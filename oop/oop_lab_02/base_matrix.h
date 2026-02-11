#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#include <cstddef>

class BaseMatrix
{
public:
    using size_type = size_t;
public:
    explicit BaseMatrix(size_type rows = 0, size_type columns = 0): _rows(rows), _cols(columns) {}
    virtual ~BaseMatrix() = default;

    virtual size_type get_row_count() const noexcept { return _rows; };
    virtual size_type get_column_count() const noexcept { return _cols; };
    
    virtual operator bool() const noexcept { return _cols && _rows; }

protected:
    size_type _rows = 0, _cols = 0;
};

#endif