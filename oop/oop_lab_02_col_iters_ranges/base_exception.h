#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <cstring>
#define ERR_MSG_LEN 1024


class BaseException: public std::exception 
{
public:
    BaseException(const time_t time_info,
                        const char* file_info,
                        const size_t line_info,
                        const char* errmsg = "No errmsg.\n");
    virtual ~BaseException() {};
    virtual const char *what() const noexcept { return _errmsg; };
protected:
    char _errmsg[ERR_MSG_LEN];
};

#include "base_exception.hpp"

#endif