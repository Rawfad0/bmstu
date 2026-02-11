#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>
#include <memory>

#include "base_iterator.h"
#include "iterator_exceptions.h"

template <MatrixType T>
class Iterator: public BaseIterator<T>
{
friend Matrix<T>;

public:
    using size_type = size_t;
    using value_type = T;
    // using value_type = std::remove_const_t<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator = Iterator<T>;
    using iterator_category = std::random_access_iterator_tag;

    Iterator() = default;
    Iterator(const Matrix<T> &matrix, const size_type index = 0): 
        _data(matrix._data), _index(index), _rows(matrix._rows), _cols(matrix._cols) {};
        
    template <typename ContainerT>
        requires Container<T, ContainerT>
    Iterator(const ContainerT &container, const size_type index = 0): 
        _data(container._data), _index(index), _rows(container._rows), _cols(container._cols) {};
    Iterator(Iterator &&iterator) noexcept = default;
    Iterator(const Iterator &iterator) = default;

    ~Iterator() noexcept = default;
    
    Iterator<T> &operator=(Iterator<T> &&other) noexcept;
    Iterator<T> &operator=(const Iterator<T> &other);
    
    T& operator*();
    const T& operator*() const;
    T& value();
    const T& value() const;
    T *operator->();
    const T *operator->() const;

    decltype(auto) operator<=>(Iterator<T> const &other) const;
    bool operator==(Iterator const &other) const;
    // bool operator!=(Iterator const &other) const;
    // bool operator>(Iterator const &other) const;
    // bool operator<(const Iterator &other) const;
    // bool operator>=(const Iterator &other) const;
    // bool operator<=(const Iterator &other) const;
    
    Iterator<T> &operator+=(const size_type value);
    Iterator<T> operator+(const size_type value) const;
    Iterator<T> &operator++();
    Iterator<T> operator++(int);
    friend Iterator<value_type> operator+(size_type value, const Iterator<value_type>& iter)
    {
        return value + iter._index;
    }
    
    Iterator<T> &operator-=(const size_type value);
    Iterator<T> operator-(const size_type value) const;
    Iterator<T> &operator--();
    Iterator<T> operator--(int);
    friend Iterator<value_type> operator-(size_type value, const Iterator<value_type>& iter)
    {
        return value - iter._index;
    }

    difference_type operator-(const Iterator<T> &other) const noexcept;
    difference_type distance(const Iterator<T> &other) const noexcept;

    T &operator[](const size_type index);
    const T &operator[](const size_type index) const;

private:
    std::weak_ptr<value_type[]> _data = nullptr;
    size_type _index = 0;
    size_type _rows = 0;
    size_type _cols = 0;
};

#include "iterator.hpp"

#endif
