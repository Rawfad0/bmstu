#include <fstream>
#include <ctime>
#include <unistd.h>

#include "logger.h"
#include "consts.h"

void log_event(const std::string& msg) {
    std::ofstream log(LOG_FILE, std::ios::app);
    if (!log.is_open()) return;

    time_t now = time(nullptr);
    char* t = ctime(&now);
    t[strlen(t) - 1] = '\0';

    log << "[" << t << "] pid=" << getpid() << " " << msg << std::endl;
}
