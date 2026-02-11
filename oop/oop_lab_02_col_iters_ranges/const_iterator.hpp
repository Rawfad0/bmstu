#include "const_iterator.h"


template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator=(ConstIterator<T> &&iterator) noexcept 
{
    this->_index = iterator._index;
    this->_data = iterator._data;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &iterator) 
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
const T &ConstIterator<T>::operator*() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
const T &ConstIterator<T>::value() const
{
    return operator*();    
}

template <MatrixType T>
const T *ConstIterator<T>::operator->() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}

template <MatrixType T>
std::partial_ordering ConstIterator<T>::operator<=>(ConstIterator<T> const &other) const 
{
    return this->_index == other._index ? std::partial_ordering::equivalent :
            this->_index < other._index ? std::partial_ordering::less :
            this->_index > other._index ? std::partial_ordering::greater :
            std::partial_ordering::unordered;
}

template <MatrixType T>
bool ConstIterator<T>::operator==(ConstIterator<T> const &other) const 
{
    return this->_index == other._index;
}

// template <MatrixType T>
// bool ConstIterator<T>::operator!=(ConstIterator<T> const &iterator) const 
// {
//     return this->_index != iterator._index;
// }

// template <MatrixType T>
// bool ConstIterator<T>::operator<(ConstIterator<T> const &other) const 
// {
//     return this->_index < other._index;
// }

// template <MatrixType T>
// bool ConstIterator<T>::operator>(ConstIterator<T> const &other) const 
// {
//     return this->_index > other._index;
// }

// template <MatrixType T>
// bool ConstIterator<T>::operator>=(ConstIterator<T> const &other) const 
// {
//     return this->_index >= other._index;
// }

// template <MatrixType T>
// bool ConstIterator<T>::operator<=(ConstIterator<T> const &other) const 
// {
//     return this->_index <= other._index;
// }

template <MatrixType T>
ConstIterator<T> ConstIterator<T>::operator+(const size_t value) const 
{
    iterator iter(*this);
    iter._index += value;

    return iter;
}

template <MatrixType T>
ConstIterator<T> ConstIterator<T>::operator-(const size_t value) const 
{
    iterator iter(*this);
    iter._index -= value;
    return iter;
}

template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator+=(const size_t value) 
{
    this->_index += value;
    return *this;
}

template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator-=(const size_t value) 
{
    this->_index -= value;
    return *this;
}

template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator++()
{
    this->_index += 1;
    return *this;
}

template <MatrixType T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
    ConstIterator<T> iter(*this);
    this->_index += 1;
    return iter;
}

template <MatrixType T>
ConstIterator<T> &ConstIterator<T>::operator--() 
{
    this->_index -= 1;
    return *this;
}

template <MatrixType T>
ConstIterator<T> ConstIterator<T>::operator--(int) 
{
    ConstIterator<T> iter(*this);
    this->_index -= 1;
    return iter;
}

template <MatrixType T>
ConstIterator<T>::difference_type ConstIterator<T>::operator-(const ConstIterator& other) const noexcept
{
    return (this->_index - other._index);
}

template <MatrixType T>
ConstIterator<T>::difference_type ConstIterator<T>::distance(const ConstIterator& other) const noexcept
{
    return other - *this;
}

template <MatrixType T>
T& ConstIterator<T>::operator[](const size_t index)
{
    return *(operator+(index));
}

template <MatrixType T>
const T& ConstIterator<T>::operator[](const size_t index) const
{
    return *(operator+(index));
}
