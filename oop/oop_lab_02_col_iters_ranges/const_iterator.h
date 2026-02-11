#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <iterator>
#include <memory>

#include "base_iterator.h"
#include "iterator_exceptions.h"

template <MatrixType T>
class ConstIterator: public BaseIterator<T>
{
public:
    using value_type = T;
    using size_type = int;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator = ConstIterator<T>;

    ConstIterator() = default;
    ConstIterator(const Matrix<T> &matrix, const size_t index = 0): 
        _data(matrix._data), _index(index), _rows(matrix._rows), _cols(matrix._cols) {};
        
    template <typename ContainerT>
        requires Container<T, ContainerT>
    ConstIterator(const ContainerT &container, const size_t index = 0): 
        _data(container._data), _index(index), _rows(container._rows), _cols(container._cols) {};
    ConstIterator(ConstIterator &&iterator) noexcept = default;
    ConstIterator(const ConstIterator &iterator) = default;

    ~ConstIterator() noexcept = default;
    
    ConstIterator<T> &operator=(ConstIterator<T> &&other) noexcept;
    ConstIterator<T> &operator=(const ConstIterator<T> &other);
    
    const T& operator*() const;
    const T& value() const;
    const T *operator->() const;

    std::partial_ordering operator<=>(ConstIterator<T> const &other) const;
    bool operator==(ConstIterator const &other) const;
    
    ConstIterator<T> &operator+=(const size_t value);
    ConstIterator<T> operator+(const size_t value) const;
    ConstIterator<T> &operator++();
    ConstIterator<T> operator++(int);
    
    ConstIterator<T> &operator-=(const size_t value);
    ConstIterator<T> operator-(const size_t value) const;
    ConstIterator<T> &operator--();
    ConstIterator<T> operator--(int);

    difference_type operator-(const ConstIterator<T> &other) const noexcept;
    difference_type distance(const ConstIterator<T> &other) const noexcept;

    T &operator[](const size_t index);
    const T &operator[](const size_t index) const;

private:
    std::weak_ptr<value_type[]> _data = nullptr;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

#include "const_iterator.hpp"

#endif
