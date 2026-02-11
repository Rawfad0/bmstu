#ifndef COLUMN_ITERATOR_H
#define COLUMN_ITERATOR_H

#include <iterator>
#include <memory>

#include "base_iterator.h"
#include "iterator_exceptions.h"

template <MatrixType T>
class ColumnIterator: public BaseIterator<T>
{
public:
    using size_type = size_t;
    using value_type = T;
    // using value_type = std::remove_const_t<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator = ColumnIterator<T>;
    using iterator_category = std::random_access_iterator_tag;

    ColumnIterator() = default;
    ColumnIterator(const Matrix<T> &matrix, const size_type index = 0): 
        _data(matrix._data), _index(index), _rows(matrix._rows), _cols(matrix._cols) {};
        
    template <typename ContainerT>
        requires Container<T, ContainerT>
    ColumnIterator(const ContainerT &container, const size_type index = 0): 
        _data(container._data), _index(index), _rows(container._rows), _cols(container._cols) {};
    ColumnIterator(ColumnIterator &&iterator) noexcept = default;
    ColumnIterator(const ColumnIterator &iterator) = default;

    ~ColumnIterator() noexcept = default;
    
    ColumnIterator<T> &operator=(ColumnIterator<T> &&other) noexcept;
    ColumnIterator<T> &operator=(const ColumnIterator<T> &other);
    
    T& operator*();
    const T& operator*() const;
    T& value();
    const T& value() const;
    T *operator->();
    const T *operator->() const;

    decltype(auto) operator<=>(ColumnIterator<T> const &other) const;
    bool operator==(ColumnIterator const &other) const;
    // bool operator!=(ColumnIterator const &other) const;
    // bool operator>(ColumnIterator const &other) const;
    // bool operator<(const ColumnIterator &other) const;
    // bool operator>=(const ColumnIterator &other) const;
    // bool operator<=(const ColumnIterator &other) const;
    
    ColumnIterator<T> &operator+=(const size_type value);
    ColumnIterator<T> operator+(const size_type value) const;
    ColumnIterator<T> &operator++();
    ColumnIterator<T> operator++(int);
    friend ColumnIterator<value_type> operator+(size_type value, const ColumnIterator<value_type>& iter)
    {
        return value + iter._index;
    }
    
    ColumnIterator<T> &operator-=(const size_type value);
    ColumnIterator<T> operator-(const size_type value) const;
    ColumnIterator<T> &operator--();
    ColumnIterator<T> operator--(int);
    friend ColumnIterator<value_type> operator-(size_type value, const ColumnIterator<value_type>& iter)
    {
        return value - iter._index;
    }

    difference_type operator-(const ColumnIterator<T> &other) const noexcept;
    difference_type distance(const ColumnIterator<T> &other) const noexcept;

    T &operator[](const size_type index);
    const T &operator[](const size_type index) const;

private:
    std::weak_ptr<value_type[]> _data = nullptr;
    size_type _index = 0;
    size_type _rows = 0;
    size_type _cols = 0;
};

#include "column_iterator.hpp"

#endif
