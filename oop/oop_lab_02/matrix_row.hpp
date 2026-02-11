#include "matrix.h"

template <MatrixType value_type>
value_type& Matrix<value_type>::MatrixRow::operator[](size_type index) const
{
    if (_matrix._cols <= index)
        throw MatrixIndexError(time(nullptr), __FILE__, __LINE__, "Incorrect column");

    return _matrix.at(_index, index);
}

template <MatrixType value_type>
Matrix<value_type>::size_type Matrix<value_type>::MatrixRow::get_size() const
{
    return this->_matrix._cols;
}

template <MatrixType value_type>
Matrix<value_type>::iterator Matrix<value_type>::MatrixRow::begin() 
{
    return Iterator<value_type>(this->_matrix, this->_index * this->get_size());
}

template <MatrixType value_type>
Matrix<value_type>::iterator Matrix<value_type>::MatrixRow::end() 
{
    return Iterator<value_type>(this->_matrix, (this->_index + 1) * this->get_size());
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::MatrixRow::begin() const 
{
    return ConstIterator<value_type>(this->_matrix, this->_index * this->get_size());
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::MatrixRow::end() const 
{
    return ConstIterator<value_type>(this->_matrix, (this->_index + 1) * this->get_size());
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::MatrixRow::cbegin() const 
{
    return ConstIterator<value_type>(this->_matrix, this->_index * this->get_size());
}

template <MatrixType value_type>
Matrix<value_type>::const_iterator Matrix<value_type>::MatrixRow::cend() const 
{
    return ConstIterator<value_type>(this->_matrix, (this->_index + 1) * this->get_size());
}