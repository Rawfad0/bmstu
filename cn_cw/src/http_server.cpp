#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <vector>

#include "http_server.h"
#include "logger.h"
#include "consts.h"

HttpRequest parse_request(const std::string &raw) {
    HttpRequest req;
    std::istringstream ss(raw);
    ss >> req.method >> req.path;
    return req;
}

static void send_status(Connection &conn, int code) {
    std::string msg;

    switch (code) {
        case 403: msg = "403 Forbidden"; break;
        case 404: msg = "404 Not Found"; break;
        case 405: msg = "405 Method Not Allowed"; break;
        default:  msg = "500 Internal Server Error";
    }

    std::string resp =
        "HTTP/1.1 " + msg + "\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n\r\n";

    size_t len = std::min(resp.size(), (size_t)BUFFER_SIZE);
    memcpy(conn.write_buf, resp.c_str(), len);
    conn.write_len = len;
    conn.write_offset = 0;
    conn.state = STATE_SEND;
}

static void prepare_response(Connection &conn) {
    std::string raw(conn.read_buf, conn.read_len);
    HttpRequest req = parse_request(raw);
    log_event(req.method + " " + req.path);

    if (req.method != "GET" && req.method != "HEAD") {
        send_status(conn, 405);
        return;
    }

    std::string path = req.path;
    if (path == "/") path = "/index.html";

    std::string full_path = std::string(DOCUMENT_ROOT) + path;

    struct stat st;
    if (stat(full_path.c_str(), &st) != 0 || !S_ISREG(st.st_mode)) {
        send_status(conn, 404);
        return;
    }

    if (access(full_path.c_str(), R_OK) != 0) {
        send_status(conn, 403);
        return;
    }

    FILE* f = fopen(full_path.c_str(), "rb");
    if (!f) {
        send_status(conn, 403);
        return;
    }

    conn.file = f;
    conn.file_size = st.st_size;

    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Length: " << st.st_size << "\r\n";
    oss << "Connection: close\r\n\r\n";

    std::string header = oss.str();
    size_t header_len = std::min(header.size(), (size_t)BUFFER_SIZE);
    memcpy(conn.write_buf, header.c_str(), header_len);
    conn.write_len = header_len;
    conn.write_offset = 0;

    if (req.method == "HEAD") {
        fclose(conn.file);
        conn.file = nullptr;
    }
    conn.state = STATE_SEND;
}

void handle_connections(std::vector<Connection> &connections, int listen_fd) {
    fd_set readfds, writefds;
    int max_fd;

    while (true) {
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);

        FD_SET(listen_fd, &readfds);
        max_fd = listen_fd;

        for (auto &conn : connections) {
            if (conn.state == STATE_READ) 
                FD_SET(conn.fd, &readfds);
            if (conn.state == STATE_SEND) 
                FD_SET(conn.fd, &writefds);
            if (conn.fd > max_fd) 
                max_fd = conn.fd;
        }

        int ret = select(max_fd + 1, &readfds, &writefds, nullptr, nullptr);
        if (ret <= 0) 
            continue;

        if (FD_ISSET(listen_fd, &readfds)) {
            int client_fd = accept(listen_fd, nullptr, nullptr);
            if (client_fd >= 0) {
                int flags = fcntl(client_fd, F_GETFL, 0);
                fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

                Connection c{};
                c.fd = client_fd;
                c.state = STATE_READ;
                c.read_len = 0;
                c.write_len = 0;
                c.write_offset = 0;
                c.file = nullptr;
                c.file_size = 0;

                connections.push_back(c);
            }
        }

        for (size_t i = 0; i < connections.size();) {
            auto &conn = connections[i];

            if (conn.state == STATE_READ && FD_ISSET(conn.fd, &readfds)) {
                ssize_t n = recv(conn.fd, conn.read_buf + conn.read_len, BUFFER_SIZE - conn.read_len, 0);
                if (n > 0) {
                    conn.read_len += n;
                    if (std::string(conn.read_buf, conn.read_len).find("\r\n\r\n") != std::string::npos) {
                        prepare_response(conn);
                    }
                } else {
                    conn.state = STATE_COMPLETE;
                }
            }

            if (conn.state == STATE_SEND && FD_ISSET(conn.fd, &writefds)) {
                if (conn.write_offset < conn.write_len) {
                    ssize_t n = send(conn.fd, conn.write_buf + conn.write_offset, conn.write_len - conn.write_offset, 0);
                    if (n > 0) 
                        conn.write_offset += n;
                    if (conn.write_offset < conn.write_len) { 
                        i++; 
                        continue; 
                    }
                }

                if (conn.file) {
                    size_t n = fread(conn.write_buf, 1, BUFFER_SIZE, conn.file);
                    if (n > 0) {
                        conn.write_len = n;
                        conn.write_offset = 0;
                        ssize_t s = send(conn.fd, conn.write_buf, conn.write_len, 0);
                        if (s > 0)
                            conn.write_offset += s;
                    }
                    if (feof(conn.file)) {
                        fclose(conn.file);
                        conn.file = nullptr;
                        conn.state = STATE_COMPLETE;
                    }
                } else if (conn.write_offset >= conn.write_len) {
                    conn.state = STATE_COMPLETE;
                }
            }

            if (conn.state == STATE_COMPLETE) {
                close(conn.fd);
                connections.erase(connections.begin() + i);
            } else {
                ++i;
            }
        }
    }
}
