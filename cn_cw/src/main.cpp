#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include "consts.h"
#include "http_server.h"
#include "logger.h"

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(listen_fd, SOMAXCONN) < 0) {
        perror("lsiten error");
        exit(1);
    }

    log_event("Server started");

    for (int i = 0; i < WORKER_COUNT; i++) {
        if (fork() == 0) {
            std::vector<Connection> connections;
            handle_connections(connections, listen_fd);
            exit(0);
        }
    }

    while (true)
        pause();
}
