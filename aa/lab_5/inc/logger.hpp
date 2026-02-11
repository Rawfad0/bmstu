#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>

class Logger
{
public:
    explicit Logger(const std::string &file_name) {
        log_file.open(file_name);
        if (!log_file) {
            throw std::runtime_error("ERROR: Can't open log file - " + file_name);
        }
    }
    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    void log(const std::string &message) {
        std::string time_stamp = get_time();
        log_file << time_stamp + " " + message << std::endl;
    }


private:
    std::string get_time() {
        std::ostringstream oss;
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        oss << std::put_time(std::localtime(&time_t_now), "%H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
        return oss.str();
    };

    std::ofstream log_file;
};

#endif // LOGGER_HPP
