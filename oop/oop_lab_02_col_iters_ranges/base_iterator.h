#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <memory>
#include "concepts.h"
#include "iterator_exceptions.h"

template <MatrixType T>
class BaseIterator
{
public:
    const T& operator*() const;
    const T& value() const;
    const T *operator->() const;

protected: 
    BaseIterator() = default;
    virtual ~BaseIterator() = default;
    
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

#include "base_iterator.hpp"

#endif
