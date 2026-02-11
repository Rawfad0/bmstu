#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <iterator>


template <typename T>
concept MatrixType = std::semiregular<T>;

template<typename T, typename U>
concept Constructable = std::constructible_from<U, T>;

template <typename T>
concept Float = requires
{
    requires MatrixType<T>;
    requires std::floating_point<T>;
};

template <typename T>
concept MathConcept = requires(T a, T b)
{
    {a + b} -> std::convertible_to<T>;
    {a * b} -> std::convertible_to<T>;
};

template <typename T>
concept Equable = requires
{
    requires MatrixType<T>;
    requires std::equality_comparable<T>;
};

template <typename T, typename U>
concept Comparable = std::totally_ordered_with<T, U>;

template <typename T, typename U>
concept Calcable = requires(T a, U b)
{
    requires std::constructible_from<U, T>;
    {a + b} -> std::convertible_to<T>;
    {a - b} -> std::convertible_to<T>;
    {a * b} -> std::convertible_to<T>;
    {a / b} -> std::convertible_to<T>;
};

template <typename T>
concept Range = requires(T u) 
{
    {u.begin()} -> std::input_iterator;
    {u.end()} -> std::sentinel_for<decltype(u.begin())>;
    requires std::constructible_from<T, typename std::iterator_traits<decltype(u.begin())>::reference>;
};

template <typename T, typename C>
concept Container = requires(C c)
{
    typename C::value_type;
	typename C::iterator;
	typename C::const_iterator;
	typename C::size_type;

    { c.empty() } noexcept -> std::same_as<bool>;
    { c.get_row_count() } noexcept -> std::same_as<typename T::size_type>;
    { c.get_column_count() } noexcept -> std::same_as<typename T::size_type>;
};

template <typename T>
concept RandomAccessIter = requires(T i, const T j, const size_t n)
{
    typename T::value_type;
    typename T::pointer;
    typename T::reference;
    typename T::difference_type;
    typename T::iterator_category;
    { std::is_same_v<typename T::iterator_category, std::random_access_iterator_tag> } -> std::same_as<const bool&>;

    { i += n } -> std::same_as<T&>;
    { j +  n } -> std::same_as<T>;
    { n +  j } -> std::same_as<T>;
    { i -= n } -> std::same_as<T&>;
    { j -  n } -> std::same_as<T>;
};

template <MatrixType T>
class Matrix;

#endif
