#ifndef ITERATOR_EXCEPTION_H
#define ITERATOR_EXCEPTION_H

#include "base_exception.h"

class IteratorIndexError: public BaseException
{
public:
    IteratorIndexError(const time_t time, const char* file, const size_t line, const char* errmsg = "IteratorIndexError\n"):
        BaseException(time, file, line, errmsg) {}
};

class IteratorDataExpiredError: public BaseException
{
public:
    IteratorDataExpiredError(const time_t time, const char* file, const size_t line, const char* errmsg = "IteratorDataExpiredError\n"):
        BaseException(time, file, line, errmsg) {}
};


#endif