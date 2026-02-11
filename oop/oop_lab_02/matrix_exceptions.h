#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

#include "base_exception.h"

class MatrixIndexError: public BaseException
{
public:
    MatrixIndexError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixIndexError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixSizeError: public BaseException
{
public:
    MatrixSizeError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixSizeError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixEmptyError: public BaseException
{
public:
    MatrixEmptyError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixEmptyError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixAllocError: public BaseException
{
public:
    MatrixAllocError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixAllocError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixOperationError: public BaseException
{
public:
    MatrixOperationError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixOperationError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixDivisionError: public BaseException
{
public:
    MatrixDivisionError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixDivisionError\n"):
        BaseException(time, file, line, errmsg) {}
};

class MatrixArgError: public BaseException
{
public:
    MatrixArgError(const time_t time, const char* file, const size_t line, const char* errmsg = "MatrixArgError\n"):
        BaseException(time, file, line, errmsg) {}
};

#endif
