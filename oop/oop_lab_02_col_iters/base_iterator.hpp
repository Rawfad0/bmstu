#include "base_iterator.h"

template <MatrixType T>
const T &BaseIterator<T>::operator*() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index];
}

template <MatrixType T>
const T &BaseIterator<T>::value() const
{
    return operator*();    
}

template <MatrixType T>
const T *BaseIterator<T>::operator->() const
{
    if (this->_data.expired())
        throw IteratorDataExpiredError(time(nullptr), __FILE__, __LINE__);
    if (this->_index >= this->_rows * this->_cols)
        throw IteratorIndexError(time(nullptr), __FILE__, __LINE__);
    std::shared_ptr<T[]> data_ptr = this->_data.lock();
    return data_ptr[_index].getAddr();
}