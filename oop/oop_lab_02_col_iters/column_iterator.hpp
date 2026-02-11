#include "column_iterator.h"


template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator=(ColumnIterator<T> &&iterator) noexcept 
{
    this->_index = iterator._index;
    this->_data = iterator._data;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator=(const ColumnIterator<T> &iterator) 
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
T &ColumnIterator<T>::operator*()
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols) 
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
const T &ColumnIterator<T>::operator*() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
T &ColumnIterator<T>::value()
{
    return operator*();    
}

template <MatrixType T>
const T &ColumnIterator<T>::value() const
{
    return operator*();    
}

template <MatrixType T>
T *ColumnIterator<T>::operator->()
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}

template <MatrixType T>
const T *ColumnIterator<T>::operator->() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}

template <MatrixType T>
decltype(auto) ColumnIterator<T>::operator<=>(ColumnIterator<T> const &other) const 
{
    return this->_index <=> other._index;
    // return this->_index == other._index ? std::partial_ordering::equivalent :
    //         this->_index < other._index ? std::partial_ordering::less :
    //         this->_index > other._index ? std::partial_ordering::greater :
    //         std::partial_ordering::unordered;
}

template <MatrixType T>
bool ColumnIterator<T>::operator==(ColumnIterator<T> const &other) const 
{
    return this->_index == other._index;
}

// template <MatrixType T>
// bool ColumnIterator<T>::operator!=(ColumnIterator<T> const &iterator) const 
// {
//     return this->_index != iterator._index;
// }

// template <MatrixType T>
// bool ColumnIterator<T>::operator<(ColumnIterator<T> const &other) const 
// {
//     return this->_index < other._index;
// }

// template <MatrixType T>
// bool ColumnIterator<T>::operator>(ColumnIterator<T> const &other) const 
// {
//     return this->_index > other._index;
// }

// template <MatrixType T>
// bool ColumnIterator<T>::operator>=(ColumnIterator<T> const &other) const 
// {
//     return this->_index >= other._index;
// }

// template <MatrixType T>
// bool ColumnIterator<T>::operator<=(ColumnIterator<T> const &other) const 
// {
//     return this->_index <= other._index;
// }

template <MatrixType T>
ColumnIterator<T> ColumnIterator<T>::operator+(const size_type value) const 
{
    iterator iter(*this);
    iter._index += _cols * value;

    return iter;
}

template <MatrixType T>
ColumnIterator<T> ColumnIterator<T>::operator-(const size_type value) const 
{
    iterator iter(*this);
    iter._index -= _cols * value;
    return iter;
}

template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator+=(const size_type value) 
{
    this->_index += _cols * value;
    return *this;
}

template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator-=(const size_type value) 
{
    this->_index -= _cols * value;
    return *this;
}

template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator++()
{
    this->_index += _cols;
    return *this;
}

template <MatrixType T>
ColumnIterator<T> ColumnIterator<T>::operator++(int)
{
    ColumnIterator<T> iter(*this);
    this->_index += _cols;
    return iter;
}

template <MatrixType T>
ColumnIterator<T> &ColumnIterator<T>::operator--() 
{
    this->_index -= _cols;
    return *this;
}

template <MatrixType T>
ColumnIterator<T> ColumnIterator<T>::operator--(int) 
{
    ColumnIterator<T> iter(*this);
    this->_index -= _cols;
    return iter;
}

template <MatrixType T>
ColumnIterator<T>::difference_type ColumnIterator<T>::operator-(const ColumnIterator& other) const noexcept
{
    return (this->_index - other._index) / _cols;
}

template <MatrixType T>
ColumnIterator<T>::difference_type ColumnIterator<T>::distance(const ColumnIterator& other) const noexcept
{
    return (other - *this) / _cols;
}

template <MatrixType T>
T& ColumnIterator<T>::operator[](const size_type index)
{
    return *(operator+(index));
}

template <MatrixType T>
const T& ColumnIterator<T>::operator[](const size_type index) const
{
    return *(operator+(index));
}
