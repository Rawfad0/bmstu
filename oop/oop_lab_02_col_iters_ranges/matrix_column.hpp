#include "matrix.h"
#include "matrix.h"

template <MatrixType value_type>
value_type& Matrix<value_type>::MatrixColumn::operator[](size_type index) const
{
    if (_matrix._rows <= index)
        throw MatrixIndexError(time(nullptr), __FILE__, __LINE__, "Incorrect row");

    return _matrix.at(index, _index);
}

template <MatrixType value_type>
Matrix<value_type>::size_type Matrix<value_type>::MatrixColumn::get_size() const
{
    return this->_matrix._rows;
}

template <MatrixType value_type>
Matrix<value_type>::MatrixColumn::iterator Matrix<value_type>::MatrixColumn::begin() 
{
    return ColumnIterator<value_type>(this->_matrix, this->_index);
}

template <MatrixType value_type>
Matrix<value_type>::MatrixColumn::iterator Matrix<value_type>::MatrixColumn::end() 
{
    return ColumnIterator<value_type>(this->_matrix, (this->_matrix._cols) * (this->get_size() - 1) + this->_index + 1);
}

// template <MatrixType value_type>
// Matrix<value_type>::const_iterator Matrix<value_type>::MatrixColumn::begin() const 
// {
//     return ConstIterator<value_type>(this->_matrix, this->_index);
// }

// template <MatrixType value_type>
// Matrix<value_type>::const_iterator Matrix<value_type>::MatrixColumn::end() const 
// {
//     return ConstIterator<value_type>(this->_matrix, (this->_matrix._cols) * (this->get_size() - 1) + this->_index + 1);
// }

// template <MatrixType value_type>
// Matrix<value_type>::const_iterator Matrix<value_type>::MatrixColumn::cbegin() const 
// {
//     return ConstIterator<value_type>(this->_matrix, this->_index);
// }

// template <MatrixType value_type>
// Matrix<value_type>::const_iterator Matrix<value_type>::MatrixColumn::cend() const 
// {
//     return ConstIterator<value_type>(this->_matrix, (this->_matrix._cols) * (this->get_size() - 1) + this->_index + 1);
// }
