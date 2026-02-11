#include <algorithm>
#include <numeric>
#include "matrix.h"

// template <MatrixType value_type>
// Matrix<value_type>& Matrix<value_type>::make_identity() requires MathConcept<value_type>
// {
//     if (!this->is_square())
//         throw MatrixOperationError(time(nullptr), __FILE__, __LINE__, "This matrix is not square, transposition is not availiable.");
//     Matrix<value_type> tmp_matrix(this->_rows, this->_cols);
//     std::ranges::for_each(*this, [](auto& element) { element = 0; });
//     for (size_t i = 0; i < this->_cols; i++)
//         (*this)[i][i] = 1;

//     return tmp_matrix;
// }

template <MatrixType value_type>
bool Matrix<value_type>::is_square() const
{
    return this->_cols == this->_rows && this->_rows != 0;
}

template <MatrixType value_type>
bool Matrix<value_type>::is_invertible() const
{
    return this->is_square() && this->determinant() != 0;
}

template <MatrixType value_type>
bool Matrix<value_type>::is_identity() const
    requires MathConcept<value_type>
{
    if (!this->is_square())
        return false;

    for (size_t i = 0; i < this->_cols; i++)
        for (size_t j = 0; j < this->_cols; j++)
            if ((*this)[i][j] != (*this)[i][j] || (i != j && (*this)[i][j] != 0) || (i == j && (*this)[i][j] == 0))
                return false;

    return true;
}

template <MatrixType value_type>
Matrix<value_type> Matrix<value_type>::transpose() const
{
    Matrix<value_type> tmp_matrix(*this);

    for (size_t i = 0; i < this->_cols; i++)
        for (size_t j = 0; j < this->_rows; j++)
            tmp_matrix[i][j] = (*this)[j][i];

    return tmp_matrix;
}

template <MatrixType value_type>
value_type Matrix<value_type>::determinant() const requires MathConcept<value_type>
{
    Matrix<value_type> U(*this);
    Matrix<value_type> L(this->_rows, this->_cols);

    for (size_t i = 0; i < this->_cols; i++)
        for (size_t j = i; j < this->_cols; j++)
            if (U[i][i] != 0)
                L[j][i] = U[j][i] / U[i][i];
            else
                throw MatrixDivisionError(time(nullptr), __FILE__, __LINE__);

    for (size_t k = 1; k < this->_cols; k++) {
        for (size_t i = k - 1; i < this->_cols; i++)
            for (size_t j = i; j < this->_cols; j++)
                if (U[i][i] != 0)
                    L[j][i] = U[j][i] / U[i][i];
                else
                    throw MatrixDivisionError(time(nullptr), __FILE__, __LINE__);

        for (size_t i = k; i < this->_cols; i++)
            for (size_t j = k - 1; j < this->_cols; j++)
                U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
    }

    value_type prov = U[0][0];

    for (size_t i = 1; i < this->_cols; i++) prov *= U[i][i];

    return prov;
}

template <MatrixType value_type>
Matrix<value_type> Matrix<value_type>::inverse() const requires MathConcept<value_type>
{
    if (!this->is_invertible())
        throw MatrixOperationError(time(nullptr), __FILE__, __LINE__, "Inversion is not possible. Matrix is not invertible");

    Matrix<value_type> tmp_matrix(*this), result(this->_cols, this->_cols);
    for (size_t j = 0; j < this->_cols; j++) 
    {
        if (tmp_matrix[j][j] == 0) 
        {
            size_t k = j;
            for (; k < this->_cols && tmp_matrix[j][k] == 0; k++);
            std::swap_ranges(tmp_matrix.begin() + j * this->_cols,
                             tmp_matrix.begin() + (j + 1) * this->_cols,
                             tmp_matrix.begin() + k * this->_cols);
        }
        value_type divide = tmp_matrix[j][j];
        std::for_each_n(tmp_matrix.begin() + j * tmp_matrix.get_column_count(), tmp_matrix.get_column_count(), [divide](auto& x) { x /= divide; });
        std::for_each_n(result.begin() + j * result.get_column_count(), result.get_column_count(), [divide](auto& x) { x /= divide; });
        for (size_t i = 0; i < this->_cols; i++) {
            if (i == j) 
                continue;
            value_type buf_1 = tmp_matrix[i][j];
            for (size_t k = 0; k < this->_cols; k++)
            {
                tmp_matrix[i][k] -= buf_1 * tmp_matrix[j][k];
                result[i][k] -= buf_1 * result[j][k];
            }
        }
    }
    return result;
}


template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::sum_matrix(const Matrix<U>& matrix)
{
    (*this) += matrix;

    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::sum_matrix(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);

    tmp_matrix += matrix;

    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::sum_value(const U& value)
{
    (*this) += value;

    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::sum_value(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);

    tmp_matrix += value;

    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::sub_value(const U& value)
{
    (*this) -= value;

    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::sub_value(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);

    tmp_matrix -= value;

    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::sub_matrix(const Matrix<U>& matrix)
{
    (*this) -= matrix;

    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::sub_matrix(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix -= matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::mul_matrix(const Matrix<U>& matrix)
{
    (*this) *= matrix;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::mul_matrix(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix *= matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::div_value(const U& value)
{
    (*this) /= value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::div_value(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix /= value;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::div_matrix(const Matrix<U>& matrix)
{
    (*this) /= matrix;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::div_matrix(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix /= matrix;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::mul_value(const U& value)
{
    (*this) *= value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::mul_value(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix *= value;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator+=(const Matrix<U>& matrix)
{
    if (this->_rows != matrix.get_row_count() || this->_cols != matrix.get_row_count())
        throw MatrixSizeError(time(nullptr), __FILE__,  __LINE__);
    std::transform(this->begin(), this->end(), matrix.begin(), this->begin(), [](auto& left, auto& right) { return left + right; });
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator+=(const U& value)
{
    for (auto & elem : *this) elem += value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator-=(const Matrix<U>& matrix)
{
    if (this->_rows != matrix.get_row_count() || this->_cols != matrix.get_row_count())
        throw MatrixSizeError(time(nullptr), __FILE__,  __LINE__);
    std::transform(this->begin(), this->end(), matrix.begin(), this->begin(), [](auto& left, auto& right) { return left - right; });
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator-=(const U& value)
{
    for (auto & elem : *this) elem -= value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator*=(const Matrix<U>& matrix)
{
    if (this->_cols != matrix.get_row_count())
        throw MatrixOperationError(time(nullptr), __FILE__, __LINE__, "Incorrect count of rows vs columns for mul.");
    Matrix<value_type> tmp_matrix(this->_rows, matrix.get_column_count());
    for (size_t i = 0; i < tmp_matrix.get_column_count(); i++) {
        Matrix<value_type> tmp_matrix_col(1, matrix.get_row_count());
        for (size_t j = 0; j < matrix.get_row_count(); j++)
            tmp_matrix_col[0][j] = matrix[j][i];
        for (size_t j = 0; j < tmp_matrix.get_row_count(); j++)
            tmp_matrix[j][i] = std::inner_product(tmp_matrix_col.begin(), tmp_matrix_col.end(), this->begin() + j * this->_cols, 0);
    }
    *this = tmp_matrix;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator*=(const U& value)
{
    // if (this->_cols == 0 || this->_rows == 0)
    //     throw MatrixEmptyError(time(nullptr), __FILE__, __LINE__);
    for (auto & elem : *this)
        elem *= value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator/=(const U& value)
{
    if (value == 0)
        throw MatrixDivisionError(time(nullptr), __FILE__, __LINE__);
    // if (this->_cols == 0 || this->_rows == 0)
    //     throw MatrixEmptyError(time(nullptr), __FILE__, __LINE__);
    for (auto& x : *this)
        x /= value;
    return *this;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
Matrix<value_type>& Matrix<value_type>::operator/=(const Matrix<U>& matrix)
{
    if (this->_cols != matrix.get_row_count())
        throw MatrixOperationError(time(nullptr), __FILE__, __LINE__, "Incorrect count of rows vs columns for div.");
    Matrix<value_type> tmp_matrix(matrix);
    tmp_matrix.inverse();
    return this->mul_matrix(tmp_matrix);
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator+(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix += matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator+(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix += value;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator-(const Matrix<U>& matrix) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix -= matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator-(const U& value) const
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix -= value;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator*(const Matrix<U>& matrix) const 
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix *= matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator*(const U& value) const 
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix *= value;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator/(const Matrix<U>& matrix) const 
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix /= matrix;
    return tmp_matrix;
}

template <MatrixType value_type>
template <typename U>
    requires Calcable<value_type, U>
decltype(auto) Matrix<value_type>::operator/(const U& value) const 
{
    Matrix<value_type> tmp_matrix(*this);
    tmp_matrix /= value;
    return tmp_matrix;
}

template<MatrixType value_type> 
Matrix<value_type> Matrix<value_type>::identity_matrix(size_type size)
{
    Matrix<value_type> id_matrix(size, size);
    for (size_t i = 0; i < id_matrix._rows; i++)
        for (size_t j = 0; j < id_matrix._cols; j++)
            if (i == j)
                id_matrix[i][j] = 1;
            else
                id_matrix[i][j] = 0;
    return id_matrix;
}

template<MatrixType value_type>
Matrix<value_type> Matrix<value_type>::zero_matrix(const size_type rows, const size_type columns)
{
    Matrix<value_type> zero_matrix(rows, columns);
    for (size_t i = 0; i < zero_matrix._rows; i++)
        for (size_t j = 0; j < zero_matrix._cols; j++)
            zero_matrix[i][j] = 0;
    return zero_matrix;
}

template<MatrixType value_type>
Matrix<value_type> Matrix<value_type>::power(long power) const requires MathConcept<value_type>
{
    if (!this->is_square())
        throw MatrixOperationError(time(nullptr), __FILE__, __LINE__, "This matrix is not square, transposition is not availiable.");
    
    if (power == 0)
        return this->identity_matrix(this->_rows);

    if (power == 1)
        return Matrix<value_type>(*this);

    Matrix<value_type> res(*this);

    for (size_t i = 1; i < static_cast<size_t>(labs(power)); ++i)
        res *= (*this);

    if (power < 0)
        res = res.inverse();

    return res;
}
