#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>
#include <vector>
#include <cstdio>
#include "consts.h"

enum State {
    STATE_READ,
    STATE_SEND,
    STATE_COMPLETE
};

struct Connection {
    int fd;
    State state;

    char read_buf[BUFFER_SIZE];
    size_t read_len;

    char write_buf[BUFFER_SIZE];
    size_t write_len;
    size_t write_offset;

    FILE* file;
    size_t file_size;
};

struct HttpRequest {
    std::string method;
    std::string path;
};

void handle_connections(std::vector<Connection> &connections, int listen_fd);

#endif

