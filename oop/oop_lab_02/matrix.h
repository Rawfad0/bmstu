#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <ranges>

#include "concepts.h"
#include "base_matrix.h"
#include "matrix_exceptions.h"
#include "iterator.h"
#include "const_iterator.h"

template <MatrixType T>
class Matrix: public BaseMatrix
{
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator = Iterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    class MatrixRow;
    class MatrixColumn;
    friend iterator;
    friend const_iterator;
public:
    Matrix() = default;
    Matrix(const size_type rows, const size_type columns);
    Matrix(const size_type rows, const size_type columns, const value_type &filler);
    Matrix(const size_type rows, const size_type columns, value_type **matrix);
    
    explicit Matrix(const Matrix<value_type> &matrix);
    template <MatrixType U>
        requires Constructable<value_type, U>
    explicit Matrix(const Matrix<U> &matrix);

    template <typename ContainerT>
        requires Container<value_type, ContainerT>
    explicit Matrix(const ContainerT &matrix_container);

    template <RandomAccessIter Iter>
        requires std::same_as<std::iter_value_t<Iter>, value_type>
    Matrix(Iter begin, Iter end, const int rows);
    Matrix(std::initializer_list<std::initializer_list<value_type>> init_list);
    explicit Matrix(Range auto range, const size_type column_size);

    Matrix(Matrix<value_type> &&matrix) noexcept;
    ~Matrix() noexcept = default;

    Matrix<value_type> &operator=(const Matrix<value_type> &matrix);
    Matrix<value_type> &operator=(Matrix<value_type> &&matrix);
    Matrix<value_type> &operator=(std::initializer_list<std::initializer_list<value_type>> list);
    template <MatrixType U>
    Matrix<value_type> &operator=(const Matrix<U> &matrix);
    template <typename ContainerT>
        requires Container<value_type, ContainerT>
    Matrix<value_type> &operator=(const ContainerT &matrix);
    
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator+(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator+=(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator+(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator+=(const U &value);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) sum_matrix(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &sum_matrix(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) sum_value(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &sum_value(const U &value);

    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator-(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator-=(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator-(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator-=(const U &value);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) sub_matrix(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &sub_matrix(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) sub_value(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &sub_value(const U &value);
    
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator*(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator*=(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator*(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator*=(const U &value);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) mul_matrix(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &mul_matrix(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) mul_value(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &mul_value(const U &value);

    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator/(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator/=(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) operator/(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &operator/=(const U &value);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) div_matrix(const Matrix<U> &matrix) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &div_matrix(const Matrix<U> &matrix);
    template <typename U> requires Calcable<value_type, U>
    decltype(auto) div_value(const U &value) const;
    template <typename U> requires Calcable<value_type, U>
    Matrix<value_type> &div_value(const U &value);

    template <typename U>
        requires Equable<U>
    bool operator==(const Matrix<U> &matrix) const;

    bool is_square() const;
    Matrix<value_type> transpose() const;
    value_type determinant() const requires MathConcept<value_type>;
    bool is_invertible() const;
    Matrix<value_type> inverse() const requires MathConcept<value_type>;
    bool is_identity() const requires MathConcept<value_type>;
    Matrix<value_type> power(long power) const requires MathConcept<value_type>;

    value_type **make_c_matrix() const;

    static Matrix<value_type> identity_matrix(const size_type size);
    static Matrix<value_type> zero_matrix(const size_type rows, const size_type columns);

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_iterator begin() const;
    const_iterator end() const;

    size_type size() const;

    MatrixRow operator[](size_type row) const;
    value_type &operator()(size_type row, size_type col);
    value_type& at(size_type row, size_type col) const;

    MatrixRow get_row(size_type row) const;
    MatrixColumn get_column(size_type column) const;

    template <MatrixType U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);

public:
    class MatrixRow 
    {
    public:
        using iterator = Iterator<value_type>;
        using const_iterator = ConstIterator<value_type>;
        friend Matrix;
        friend iterator;
        friend const_iterator;
    public:
        MatrixRow(const Matrix<value_type>& matrix, size_type index): _matrix(matrix), _index(index){};
        MatrixRow(const Matrix<value_type>& matrix): _matrix(matrix), _index(0){};
        ~MatrixRow() = default;

        value_type& operator[](size_type index) const;
        
        size_type get_size() const;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator begin() const;
        const_iterator end() const;

    private:
        const Matrix<value_type>& _matrix;
        size_type _index;
    };

    class MatrixColumn 
    {
        friend Matrix;
        friend iterator;
        friend const_iterator;
    public:
        MatrixColumn(const Matrix<value_type>& matrix, size_type index): _matrix(matrix), _index(index){};
        MatrixColumn(const Matrix<value_type>& matrix): _matrix(matrix), _index(0){};
        ~MatrixColumn() = default;

        value_type& operator[](size_type index) const;
        
        size_type get_size() const;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator begin() const;
        const_iterator end() const;

    private:
        const Matrix<value_type>& _matrix;
        size_type _index;
    };

private:
    std::shared_ptr<value_type[]> _data = nullptr;
    void _allocate(size_type size);
};

#include "matrix.hpp"
#include "matrix_math.hpp"
#include "matrix_row.hpp"
#include "matrix_column.hpp"

#endif