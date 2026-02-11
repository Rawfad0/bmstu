// #include <algorithm>
// #include <numeric>

#include "matrix.h"

template <MatrixType value_type>
Matrix<value_type>::Matrix(const size_type rows, const size_type columns): BaseMatrix(rows, columns)
{
    _allocate(rows * columns);
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(const size_type rows, const size_type columns, const value_type &filler): BaseMatrix(rows, columns)
{
    _allocate(rows * columns);
    for (size_type i = 0; i < rows; ++i)
        for (size_type j = 0; j < columns; ++j)
            _data[i * _cols + j] = filler;
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(const Matrix<value_type> &matrix): BaseMatrix(matrix._rows, matrix._cols) 
{
    _allocate(matrix._rows * matrix._cols);
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = matrix[i][j];
}

template <MatrixType value_type>
template <MatrixType U>
    requires Constructable<value_type, U>
Matrix<value_type>::Matrix(const Matrix<U> &matrix): BaseMatrix(matrix.get_row_count(), matrix.get_column_count()) 
{
    _allocate(matrix._rows * matrix._cols);
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = matrix[i][j];
}

template <MatrixType value_type>
template <RandomAccessIter Iter>
        requires std::same_as<std::iter_value_t<Iter>, value_type>
Matrix<value_type>::Matrix(const Iter begin, const Iter end, const int rows)
{
    size_t len = end - begin;
    if (len == 0 || len % rows != 0)
    {
        throw MatrixArgError(time(nullptr), __FILE__, __LINE__, "Incorrect rows param");
    }

    _cols = rows;
    _rows = len / rows;
    _allocate(_rows * _cols);
    
    Iter beg = begin;
    for (size_t i = 0; i < len; i++, beg++)
        this->_data[i] = *beg;
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(Range auto range, const size_type rows): BaseMatrix() 
{
    size_type rows_num = 0;
    for (auto iter = std::begin(range); iter != std::end(range); iter++, rows_num++);

    if (rows_num == 0 || rows_num % rows != 0)
        throw MatrixArgError(time(nullptr), __FILE__, __LINE__, "Incorrect rows param");

    _cols = rows;
    _rows = rows_num / rows;
    _allocate(_rows * _cols);

    std::ranges::copy(std::begin(range), std::end(range), this->begin());
}

template <MatrixType value_type>
template <typename ContainerT>
    requires Container<value_type, ContainerT>
Matrix<value_type>::Matrix(const ContainerT& container): BaseMatrix(container.get_row_count(), container.get_column_count())
{
    _allocate(container.get_row_count() * container.get_columns_count());
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = container[i][j];
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(Matrix<value_type>&& matrix) noexcept: BaseMatrix(matrix.get_row_count(), matrix.get_column_count()) 
{
    _data = matrix._data;
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(const size_type rows, const size_type columns, value_type **matrix): BaseMatrix(rows, columns) 
{
    if(matrix != nullptr)
        throw MatrixArgError(time(nullptr), __FILE__, __LINE__, "Incorrect matrix pointer");
    _allocate(rows * columns);
    for (size_type i = 0; i < rows; ++i)
    {
        if(matrix[i] != nullptr)
            throw MatrixArgError(time(nullptr), __FILE__, __LINE__, "Incorrect matrix pointer");
        for (size_type j = 0; j < columns; ++j)
            _data[i * _cols + j] = matrix[i][j];
    }
}

template <MatrixType value_type>
Matrix<value_type>::Matrix(std::initializer_list<std::initializer_list<value_type>> init_list): BaseMatrix(init_list.size(), init_list.begin()->size()) 
{
    size_type rows = init_list.size();
    auto it = init_list.begin();
    size_type cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols)
            throw MatrixSizeError(time(nullptr), __FILE__, __LINE__, "Incorrect initializer list size");

    _allocate(rows * cols);
    _rows = rows;
    _cols = cols;
    size_type i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data[i] = elem;
            ++i;
        }
}

template <MatrixType value_type>
Matrix<value_type>& Matrix<value_type>::operator=(const Matrix<value_type>& matrix) 
{
    _allocate(matrix._rows * matrix._cols);
    _rows = matrix._rows;
    _cols = matrix._cols;
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = matrix[i][j];

    return *this;
}

template <MatrixType value_type>
Matrix<value_type>& Matrix<value_type>::operator=(Matrix<value_type>&& matrix) 
{
    _rows = matrix.get_row_count();
    _cols = matrix.get_column_count();
    _data = matrix._data;

    return *this;
}

template <MatrixType value_type>
template <MatrixType U>
Matrix<value_type>& Matrix<value_type>::operator=(const Matrix<U>& matrix) 
{
    _allocate(matrix._rows * matrix._cols);
    _rows = matrix._rows;
    _cols = matrix._cols;
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = matrix[i][j];

    return *this;
}

template <MatrixType value_type>
template <typename ContainerT>
    requires Container<value_type, ContainerT>
Matrix<value_type>& Matrix<value_type>::operator=(const ContainerT& matrix) 
{
    _rows = matrix.get_row_count();
    _cols = matrix.get_columns_count();
    _allocate(_rows * _cols);
    for (size_type i = 0; i < _rows; ++i)
        for (size_type j = 0; j < _cols; ++j)
            _data[i * _cols + j] = matrix[i][j];

    return *this;
}

template <MatrixType value_type>
Matrix<value_type>& Matrix<value_type>::operator=(std::initializer_list<std::initializer_list<value_type>> init_list) 
{
    size_type rows = init_list.size();
    auto it = init_list.begin();
    size_type cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols)
            throw MatrixSizeError(time(nullptr), __FILE__, __LINE__, "Incorrect initializer list size");

    _allocate(rows * cols);
    _rows = rows;
    _cols = cols;
    size_type i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data[i] = elem;
            ++i;
        }

    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Equable<U>
bool Matrix<value_type>::operator==(const Matrix<U>& matrix) const
{
    return std::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
}

// template <MatrixType value_type>
// template <typename U>
//     requires Equable<U>
// bool Matrix<value_type>::operator!=(const Matrix<U>& matrix) const 
// {
//     return !std::ranges::equal(this->begin(), this->end(), matrix.begin(), matrix.end());
// }

template <MatrixType value_type>
Matrix<value_type>::MatrixRow Matrix<value_type>::operator[](const size_type row) const
{
    return get_row(row);
}

template <MatrixType value_type>
value_type& Matrix<value_type>::operator()(size_type row, size_type col)
{
    return this->_data[row * this->_cols + col];
}

// template <MatrixType value_type>
// const value_type& Matrix<value_type>::operator()(size_type row, size_type col) const
// {
//     return this->_data[row * this->_cols + col];
// }

template <MatrixType value_type>
value_type& Matrix<value_type>::at(size_type row, size_type col) const
{
    return this->_data[row * this->_cols + col];
}

template <MatrixType value_type>
Matrix<value_type>::iterator Matrix<value_type>::begin() 
{
    return Iterator<value_type>(*this, 0);
}

template <MatrixType value_type>
Matrix<value_type>::iterator Matrix<value_type>::end() 
{
    return Iterator<value_type>(*this, this->_rows * this->_cols);
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::begin() const 
{
    return ConstIterator<value_type>(*this, 0);
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::end() const 
{
    return ConstIterator<value_type>(*this, this->_rows * this->_cols);
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::cbegin() const 
{
    return ConstIterator<value_type>(*this, 0);
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::cend() const 
{
    return ConstIterator<value_type>(*this, this->_rows * this->_cols);
}

template <MatrixType value_type>
Matrix<value_type>::size_type Matrix<value_type>::size() const 
{
    return this->_rows * this->_cols;
}

template <MatrixType value_type>
void Matrix<value_type>::_allocate(size_type size)
{
    try
    {
        _data.reset(new value_type[size]);
    }
    catch (std::bad_alloc &err) 
    {
        throw MatrixAllocError(time(nullptr), __FILE__, __LINE__, "_allocate function error");
    }
}

template <MatrixType value_type>
std::ostream &operator<<(std::ostream &os, const Matrix<value_type> &matrix)
{
    for (size_t i = 0; i < matrix.get_row_count(); ++i)
    {
        for (size_t j = 0; j < matrix.get_column_count(); ++j)
            os << matrix[i][j] << " ";
        os << std::endl;
    }
    return os;
}

template<MatrixType value_type> 
value_type **Matrix<value_type>::make_c_matrix() const
{
    value_type **c_matrix = new value_type*[_rows];
    for (size_t i = 0; i < _rows; ++i) 
    {
        c_matrix[i] = new value_type[_cols];
        for (size_t j = 0; j < _cols; ++j)
            c_matrix[i][j] = _data[i * _cols + j];
    }

    return c_matrix;
}

template<MatrixType value_type> 
Matrix<value_type>::MatrixRow Matrix<value_type>::get_row(size_type row) const
{
    if (_rows <= row)
        throw MatrixIndexError(time(nullptr), __FILE__, __LINE__, "Icorrect row index.");

    return MatrixRow(*this, row);
}

template<MatrixType value_type> 
Matrix<value_type>::MatrixColumn Matrix<value_type>::get_column(size_type column) const
{    
    if (_cols <= column)
        throw MatrixIndexError(time(nullptr), __FILE__, __LINE__, "Icorrect column index.");

    return MatrixColumn(*this, column);
}
