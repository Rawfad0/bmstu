#include "iterator.h"


template <MatrixType T>
Iterator<T> &Iterator<T>::operator=(Iterator<T> &&iterator) noexcept 
{
    this->_index = iterator._index;
    this->_data = iterator._data;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &iterator) 
{
    this->_data = iterator._data;
    this->_index = iterator._index;
    this->_rows = iterator._rows;
    this->_cols = iterator._cols;
    return *this;
}

template <MatrixType T>
T &Iterator<T>::operator*()
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols) 
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
const T &Iterator<T>::operator*() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
T &Iterator<T>::value()
{
    return operator*();    
}

template <MatrixType T>
const T &Iterator<T>::value() const
{
    return operator*();    
}

template <MatrixType T>
T *Iterator<T>::operator->()
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}

template <MatrixType T>
const T *Iterator<T>::operator->() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}

template <MatrixType T>
decltype(auto) Iterator<T>::operator<=>(Iterator<T> const &other) const 
{
    return this->_index <=> other._index;
    // return this->_index == other._index ? std::partial_ordering::equivalent :
    //         this->_index < other._index ? std::partial_ordering::less :
    //         this->_index > other._index ? std::partial_ordering::greater :
    //         std::partial_ordering::unordered;
}

template <MatrixType T>
bool Iterator<T>::operator==(Iterator<T> const &other) const 
{
    return this->_index == other._index;
}

// template <MatrixType T>
// bool Iterator<T>::operator!=(Iterator<T> const &iterator) const 
// {
//     return this->_index != iterator._index;
// }

// template <MatrixType T>
// bool Iterator<T>::operator<(Iterator<T> const &other) const 
// {
//     return this->_index < other._index;
// }

// template <MatrixType T>
// bool Iterator<T>::operator>(Iterator<T> const &other) const 
// {
//     return this->_index > other._index;
// }

// template <MatrixType T>
// bool Iterator<T>::operator>=(Iterator<T> const &other) const 
// {
//     return this->_index >= other._index;
// }

// template <MatrixType T>
// bool Iterator<T>::operator<=(Iterator<T> const &other) const 
// {
//     return this->_index <= other._index;
// }

template <MatrixType T>
Iterator<T> Iterator<T>::operator+(const size_type value) const 
{
    iterator iter(*this);
    iter._index += value;

    return iter;
}

template <MatrixType T>
Iterator<T> Iterator<T>::operator-(const size_type value) const 
{
    iterator iter(*this);
    iter._index -= value;
    return iter;
}

template <MatrixType T>
Iterator<T> &Iterator<T>::operator+=(const size_type value) 
{
    this->_index += value;
    return *this;
}

template <MatrixType T>
Iterator<T> &Iterator<T>::operator-=(const size_type value) 
{
    this->_index -= value;
    return *this;
}

template <MatrixType T>
Iterator<T> &Iterator<T>::operator++()
{
    this->_index += 1;
    return *this;
}

template <MatrixType T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> iter(*this);
    this->_index += 1;
    return iter;
}

template <MatrixType T>
Iterator<T> &Iterator<T>::operator--() 
{
    this->_index -= 1;
    return *this;
}

template <MatrixType T>
Iterator<T> Iterator<T>::operator--(int) 
{
    Iterator<T> iter(*this);
    this->_index -= 1;
    return iter;
}

template <MatrixType T>
Iterator<T>::difference_type Iterator<T>::operator-(const Iterator& other) const noexcept
{
    return (this->_index - other._index);
}

template <MatrixType T>
Iterator<T>::difference_type Iterator<T>::distance(const Iterator& other) const noexcept
{
    return other - *this;
}

template <MatrixType T>
T& Iterator<T>::operator[](const size_type index)
{
    return *(operator+(index));
}

template <MatrixType T>
const T& Iterator<T>::operator[](const size_type index) const
{
    return *(operator+(index));
}
