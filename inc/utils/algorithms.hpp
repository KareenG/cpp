#pragma once

#include <iostream>
#include <functional>  // Include for std::less

namespace utils {

/**
 * @brief Fills a range with a sequence of incrementing values.
 *
 * This function assigns values to the elements in the range [begin, end), starting with a 
 * given value and incrementing sequentially.
 * 
 * @tparam Iter Type of the iterator pointing to elements in the range.
 * @tparam T Type of the value to be used for filling, which also determines the type of 
 *         increments.
 * @param begin Iterator to the beginning of the range to fill.
 * @param end Iterator to the end of the range (exclusive).
 * @param value The initial value to assign to the first element in the range.
 *
 * @note If the range [begin, end) is not valid, the function performs no action.
 * @note This function increments the value for each subsequent element, effectively 
 *       filling the range with a consecutive sequence starting at `value`.
 */
template<typename Iter, typename T>
void fill_sequence(Iter begin, Iter const& end, T value)
{
    if(std::distance(begin, end) < 0) {
        return;
    }
    while(begin != end) {
        *begin = value;
        ++begin;
        value += 1;
    }
}

/**
 * @brief Applies a unary function to each element in a given range.
 * 
 * This function iterates over each element in the range defined by [begin, end) and 
 * applies a unary function to modify each element.
 * The modification is performed in-place, updating each element with the result of the 
 * function applied to it.
 *
 * @tparam Iter Type of the iterator pointing to elements in the range.
 * @tparam UnaryFunc Type of the unary function that will be applied to elements of the 
 *         range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range (exclusive).
 * @param func Unary function that modifies elements. The function must return a value 
 *             that can be assigned to the element.
 *
 * @note If the range [begin, end) is invalid (end precedes begin), the function 
 *       performs no action.
 */
template<typename Iter, typename UnaryFunc>
void map(Iter begin, Iter const& end, UnaryFunc func)
{
    if(std::distance(begin, end) < 0) {
        return;
    }
    while(begin != end) {
        *begin = func(*begin);
        ++begin;
    }
}

/**
 * @brief Transforms elements from two input ranges by applying a binary function and 
 *        stores the result in a third range.
 * 
 * For each pair of elements from the input ranges, this function applies a binary function 
 * and stores the result in the corresponding position in the output range. The transformation 
 * is defined as: output[i] = bi_func(first[i], second[i]).
 *
 * @tparam Iter Type of the iterators pointing to the elements in the ranges.
 * @tparam BinaryFunc Type of the binary function that takes two arguments 
 *         (one from each input range) and returns a result.
 * @param first_begin Iterator to the beginning of the first input range.
 * @param first_end Iterator to the end of the first input range (exclusive).
 * @param second_begin Iterator to the beginning of the second input range.
 * @param output_begin Iterator to the beginning of the output range.
 * @param bi_func Binary function to apply to pairs of elements from the first and 
 *                second input ranges.
 *
 * @note The function assumes that the second input range and the output range are at 
 *       least as large as the distance between first_begin and first_end.
 * @note If the range [first_begin, first_end) is invalid (end precedes begin), the function 
 *       performs no action.
 */
template<typename Iter, typename BinaryFunc>
void map(Iter first_begin, Iter const& first_end, Iter second_begin, Iter output_begin, BinaryFunc bi_func)
{
    if(std::distance(first_begin, first_end) < 0) {
        return;
    }
    while(first_begin != first_end) {
        *output_begin = bi_func(*first_begin, *second_begin);
        ++first_begin;
        ++second_begin;
        ++output_begin;
    }
}

/**
 * @brief Partitions a range of elements such that all elements less than or equal to a 
 *        pivot are before all elements greater than the pivot.
 *
 * This function reorders the elements in the range [begin, end) in such a way that all 
 * elements for which the comparison element <= pivot holds
 * are placed before any elements for which this condition does not hold. This 
 * partitioning is performed in-place and does not guarantee to preserve the relative order 
 * of the elements.
 *
 * @tparam Iter Iterator type of the range.
 * @tparam T Type of the pivot value against which the elements are compared.
 * @param begin Iterator to the beginning of the range to partition.
 * @param end Iterator past the end of the range to partition.
 * @param pivot The pivot value used for partitioning the range.
 *
 * @note If the range [begin, end) is invalid (end precedes begin), the function 
 *       performs no action.
 * @note The function modifies the range in-place and requires the value type of Iter to be 
 *       swappable.
 */
template<typename Iter, typename T>
void partition(Iter begin, Iter end, T const& pivot)
{
    if(std::distance(begin, end) < 0) {
        return;
    }
    --end;
    while(begin != end) {
        while(begin != end && *begin <= pivot) {
            ++begin;
        }
        while(begin != end && *end >= pivot) {
            --end;
        }
        if(begin != end) {
            std::swap(*begin, *end);
        }
    }
}

/**
 * @brief Partitions a range of elements based on a predicate function, placing all elements 
 *        satisfying the predicate before those that do not.
 *
 * This function reorders elements in the range [begin, end) such that all elements for which 
 * the predicate returns true precede
 * all elements for which the predicate returns false. The partitioning is stable if the 
 * predicate splits the range into elements that
 * satisfy the predicate and those that do not without changing their relative order.
 *
 * @tparam Iter Type of the iterators defining the range.
 * @tparam Predicate Type of the predicate function. The function should return a 
 *         boolean value.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator past the end of the range.
 * @param predicate A unary predicate which returns `true` or `false` for an element.
 * @param predicate_f Flag to enable or disable partitioning; if zero, the function 
 *                    returns without altering the range.
 *
 * @note If the range [begin, end) is invalid (end precedes begin), the function 
 *       performs no action.
 * @note The function modifies the range in-place and requires the value type of Iter to be 
 *       swappable.
 */
template<typename Iter, typename Predicate>
void partition(Iter begin, Iter end, Predicate predicate, int predicate_f)
{
    if(!predicate_f) {
        return;
    }
    if(std::distance(begin, end) < 0) {
        return;
    }
    Iter write = begin;
    for(Iter read = begin; read != end; ++read) {
        if(predicate(*read)) {
            std::swap(*read, *write);
            ++write;
        }
    }
}

/**
 * @brief Prints elements from a range defined by two iterators to the standard output.
 *
 * This function outputs the elements within the range [begin, end) to the standard output 
 * stream (std::cout),
 * formatting them as a comma-separated list enclosed in square brackets.
 *
 * @tparam Iter Type of the iterators defining the range. Iterators must support 
 *         dereferencing to access values.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator past the end of the range.
 *
 * @note If the range [begin, end) is invalid (end precedes begin), the function 
 * performs no action.
 * @note Elements are assumed to be of a type that supports streaming via std::ostream. 
 *       If the element type does not support std::ostream operations, compilation 
 *       will fail.
 */
template<typename Iter>
void print(Iter begin, Iter end)
{
    if(std::distance(begin, end) < 0) {
        return;
    }
    std::cout << '[';
    while(begin != end) {
        if(*begin) {
            std::cout << *begin;
        }
        ++begin;
        if(begin != end) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

/**
 * @brief Prints elements from a container to the standard output.
 *
 * This function utilizes the container's const_iterators to pass the entire range of 
 * the container
 * to the previously defined range-based print function. It outputs the elements as a 
 * comma-separated list 
 * enclosed in square brackets on the standard output stream (std::cout).
 *
 * @tparam T Type of the container, which must support cbegin() and cend() to retrieve 
 *         const_iterators.
 * @param container The container from which elements are to be printed.
 *
 * @note This function delegates to the 'print(Iter begin, Iter end)' function, and as 
 *       such, the elements of the container must support streaming via std::ostream. 
 *       If the element type does not support this, compilation will fail.
 */
template<typename T>
void print(const T& container) 
{
    typename T::const_iterator it_begin = container.cbegin();
    typename T::const_iterator it_end = container.cend();
    print(it_begin, it_end);
}

/**
 * @brief Searches for the first element in a range that satisfies a specified predicate.
 *
 * Iterates over the range [begin, end) and returns the iterator to the first element for 
 * which the predicate returns true. If no such element is found, returns the end iterator.
 *
 * @tparam Iter Type of the iterator, deduced from the function arguments.
 * @tparam Predicate Type of the predicate function, which should take an element of the 
 *         type pointed to by Iter and return a bool indicating whether the element 
 *         satisfies the condition.
 * @param begin Iterator to the start of the range.
 * @param end Iterator to the end of the range.
 * @param predicate A unary predicate which returns `true` for the required element.
 *
 * @return Iterator to the first element satisfying the predicate, or end if no such 
 *         element is found.
 *
 * @note The function assumes that the range [begin, end) is valid and that begin can be 
 *       incremented to reach end. If the range is invalid (begin is further than end), it immediately returns end.
 */
template<typename Iter, typename Predicate>
Iter find_first(Iter begin, Iter const& end, Predicate predicate) 
{
    if(std::distance(begin, end) < 0) {
        return end;
    }
    while(begin != end) {
        if(predicate(*begin)) {
            return begin;
        }
        ++begin; 
    }
    return end;
}

//---------------- check prints ----------------

/**
 * @brief Prints elements from a range [begin, end) to a specified output stream.
 *
 * This function iterates over the range defined by [begin, end) and prints each element
 * to the provided output stream, formatting the output as a comma-separated list enclosed
 * in square brackets.
 *
 * @tparam Iter Type of the iterator, deduced from the function arguments.
 * @param os Reference to the output stream where the elements will be printed.
 * @param begin Iterator to the start of the range.
 * @param end Iterator to the end of the range.
 *
 * @note If the range [begin, end) is not valid (e.g., begin is after end), the function will
 *       not output anything.
 * @note This function does not check for null values; it prints each element as long as it 
 *       can be dereferenced.
 */
template<typename Iter>
void print(std::ostream& os, Iter begin, Iter end) 
{
    if(std::distance(begin, end) < 0) {
        return;
    }
    os << '[';
    while(begin != end) {
        if(*begin) {
            os << *begin;
        }
        ++begin;
        if(begin != end) {
            os << ", ";
        }
    }
    os << "]\n";
}

/**
 * @brief Prints the contents of a container to an output stream.
 * 
 * This function takes a container and prints its elements in a formatted way.
 * The elements are printed in a comma-separated list enclosed in square brackets: 
 * [elem1, elem2, ...].
 * 
 * @tparam T Type of the container (must support `cbegin()` and `cend()`).
 * @param os Output stream where the contents will be printed.
 * @param container The container whose elements are to be printed.
 * 
 * @note This function assumes that the container elements support the `<<` stream 
 * operator.
 * @note If the container is empty, it prints `[]`.
 */
template<typename T>
void print(std::ostream& os, const T& container) 
{
    typename T::const_iterator it_begin = container.cbegin();
    typename T::const_iterator it_end = container.cend();
    print(os, it_begin, it_end);
}

}   // namespace utils