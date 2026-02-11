#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr int SERVER_PORT = 32123;
constexpr int BUFFER_SIZE = 8192;

std::atomic<size_t> total_bytes{0};
std::atomic<size_t> success_connections{0};
std::atomic<size_t> failed_connections{0};

bool client_task(const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return false;
    }

    std::string request =
        "GET " + path + " HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n\r\n";

    if (send(sock, request.c_str(), request.size(), 0) <= 0) {
        close(sock);
        return false;
    }

    char buffer[BUFFER_SIZE];
    ssize_t n;
    size_t received = 0;

    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        received += n;
    }

    close(sock);

    if (received > 0) {
        total_bytes += received;
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <connections> <path>\n";
        return 1;
    }

    int connections = std::stoi(argv[1]);
    std::string path = argv[2];

    std::vector<std::thread> threads;
    std::vector<bool> results(connections);

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < connections; ++i) {
        threads.emplace_back([&, i]() {
            bool ok = client_task(path);
            results[i] = ok;
            if (ok)
                success_connections++;
            else
                failed_connections++;
        });
    }

    for (auto& t : threads)
        t.join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double seconds = elapsed.count();
    double mb = total_bytes.load() / (1024.0 * 1024.0);

    size_t success = success_connections.load();
    size_t failed = failed_connections.load();
    double success_rate = 100.0 * success / connections;

    std::cout << connections << "," << success << "," << failed << "," << success_rate << "," << mb << "," << seconds << "," << (mb / seconds) << "\n";

    // std::cout << "Connections: " << connections << "\n";
    // std::cout << "Successful: " << success << "\n";
    // std::cout << "Failed: " << failed << "\n";
    // std::cout << "Success rate: " << success_rate << " %\n";
    // std::cout << "Total data: " << mb << " MB\n";
    // std::cout << "Time: " << seconds << " s\n";
    // std::cout << "Total throughput: "
    //           << (mb / seconds) << " MB/s\n";

    // if (success > 0) {
    //     std::cout << "Per-connection throughput: "
    //               << (mb / seconds / success) << " MB/s\n";
    // }

    return 0;
}
