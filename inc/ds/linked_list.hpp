#pragma once

#include <vector>
#include <utility>  // For std::move
#include <cstddef>
#include <cassert>

namespace ds {

template <typename T>
class Iterator;

template <typename T>
class ConstIterator;

/**
 * @brief Represents a singly linked list that manages elements of type T.
 * 
 * The LinkedList class provides a series of node-based storage mechanisms,
 * allowing for efficient insertion and removal at the beginning of the list.
 * This class supports copying, moving, and iterating through items.
 *
 * @tparam T The type of elements stored in the linked list.
 */
template <typename T>
class LinkedList {
public:
        /**
     * @brief Default constructor that initializes an empty LinkedList.
     */
    LinkedList();

    /**
     * @brief Destructor that cleans up all nodes to prevent memory leaks.
     */
    ~LinkedList() noexcept;

    /**
     * @brief Constructs a LinkedList from a constant vector reference.
     * @param vec A constant reference to a vector containing initial elements.
     */
    LinkedList(std::vector<T> const& vec);

    /**
     * @brief Constructs a LinkedList by moving data from a vector.
     * @param vec An rvalue reference to a vector containing initial elements.
     */
    LinkedList(std::vector<T>&& vec);

    /**
     * @brief Copy constructor for creating a deep copy of another LinkedList.
     * @param other A reference to the LinkedList to be copied.
     */
    LinkedList(LinkedList<T> const& other);

    /**
     * @brief Move constructor for transferring ownership from another LinkedList.
     * @param other An rvalue reference to the LinkedList from which to transfer ownership.
     */
    LinkedList(LinkedList<T>&& other) noexcept;

    /**
     * @brief Copy assignment operator for deep copying from another LinkedList.
     * @param other A reference to the LinkedList to be copied.
     * @return A reference to the current LinkedList after copying.
     */
    LinkedList& operator=(LinkedList<T> const& other);

    /**
     * @brief Move assignment operator for transferring ownership from another LinkedList.
     * @param other An rvalue reference to the LinkedList from which to transfer ownership.
     * @return A reference to the current LinkedList after transferring ownership.
     */
    LinkedList& operator=(LinkedList<T>&& other) noexcept;

    /**
     * @brief Inserts an element at the beginning of the LinkedList.
     * @param element The element to insert.
     */
    void push(T const& element);

    /**
     * @brief Moves an element to the beginning of the LinkedList.
     * @param element An rvalue reference to the element to be moved.
     */
    void push(T&& element);

    /**
     * @brief Removes the first element from the LinkedList and stores it in pop_data.
     * @param pop_data A reference to a variable where the popped data will be stored.
     * @note Asserts if the list is empty to prevent undefined behavior.
     */
    void pop(T& pop_data);

    /**
     * @brief Returns the number of elements in the LinkedList.
     * @return The size of the LinkedList as a size_t.
     */
    size_t size() const noexcept;

    /**
     * @brief Checks if the LinkedList is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool empty();

    /**
     * @brief Returns an iterator to the beginning of the LinkedList.
     * @return An Iterator to the first element.
     */
    Iterator<T> begin() noexcept;

    /**
     * @brief Returns an iterator to the end of the LinkedList.
     * @return An Iterator to the theoretical element following the last element.
     */
    Iterator<T> end() noexcept;

    /**
     * @brief Returns a const iterator to the beginning of the LinkedList.
     * @return A ConstIterator to the first element.
     */
    ConstIterator<T> begin() const noexcept;

    /**
     * @brief Returns a const iterator to the end of the LinkedList.
     * @return A ConstIterator to the theoretical element following the last element.
     */
    ConstIterator<T> end() const noexcept;

    /**
     * @brief Returns a const iterator to the beginning of the LinkedList.
     * @return A ConstIterator to the first element.
     */
    ConstIterator<T> cbegin() const noexcept;

    /**
     * @brief Returns a const iterator to the end of the LinkedList.
     * @return A ConstIterator to the theoretical element following the last element.
     */
    ConstIterator<T> cend() const noexcept;

private:
    void swap(LinkedList& list);
    struct Node;
    Node* initialize_list(std::vector<T> const& vec);
    Node* initialize_list(std::vector<T> const&& vec);
    Node* initialize_list_from_other(LinkedList const& other);
    void clear(Node* start);
    
    friend class Iterator<T>;
    friend class ConstIterator<T>;

private:
    Node* head_;
    size_t size_;
};

/*-------------------------------------------------------------------------------------------*/

/**
 * @brief An iterator for navigating through a LinkedList.
 *
 * This Iterator is designed to traverse and access elements within a LinkedList.
 * It supports increment operations, dereferencing, and comparison, allowing it to
 * be used in typical C++ idiomatic ways such as range-based for loops and algorithms.
 *
 * @tparam T The type of elements stored in the linked list.
 */
template <typename T>
class Iterator {
public:
    /**
     * @brief Constructs an iterator pointing to a specific node.
     * @param node A pointer to a Node object, defaults to nullptr if not provided.
     */
    explicit Iterator(typename LinkedList<T>::Node* node = nullptr);

    /**
     * @brief Dereferences the iterator to access the data in the node it points to.
     * @return A constant reference to the data stored in the node.
     * @note Asserts if the iterator is dereferenced while pointing to nullptr.
     */
    T const& operator*() const;

    /**
     * @brief Increments the iterator to point to the next node in the LinkedList.
     * @return A reference to the updated iterator.
     * @note Asserts if incremented while pointing to nullptr (end of the list).
     */
    Iterator& operator++();

    /**
     * @brief Increments the iterator to the next node, returning the state before incrementation.
     * @return A copy of the iterator before it was incremented.
     * @note Asserts if incremented while pointing to nullptr (end of the list).
     */
    Iterator operator++(int);

    /**
     * @brief Compares two iterators for equality.
     * @param other Another iterator to compare against.
     * @return True if both iterators point to the same node, false otherwise.
     */
    bool operator==(Iterator const& other) const noexcept;

private:    
    typename LinkedList<T>::Node* node_;

};

/**
 * @brief Compares two iterators for inequality.
 * @param lhs Left-hand side iterator to compare.
 * @param rhs Right-hand side iterator to compare.
 * @return True if the iterators do not point to the same node, false otherwise.
 */
template <typename T>
bool operator!=(Iterator<T> const& lhs, Iterator<T> const& rhs) noexcept;

/*-------------------------------------------------------------------------------------------*/

/**
 * @brief A constant iterator for navigating through a LinkedList.
 *
 * The ConstIterator provides a way to traverse the LinkedList without modifying
 * the elements it accesses. It is similar to Iterator but only allows read access,
 * supporting operations suitable for examining the list contents without alteration.
 *
 * @tparam T The type of elements stored in the linked list.
 */
template <typename T>
class ConstIterator {
public:
    /**
     * @brief Constructs a const iterator pointing to a specific node.
     * @param node A pointer to a const Node object, defaults to nullptr if not provided.
     */
    explicit ConstIterator(const typename LinkedList<T>::Node* node = nullptr);

    /**
     * @brief Dereferences the const iterator to access the data in the node it points to.
     * @return A constant reference to the data stored in the node.
     * @note Asserts if the const iterator is dereferenced while pointing to nullptr.
     */
    T const& operator*() const;

    /**
     * @brief Increments the const iterator to point to the next node in the LinkedList.
     * @return A reference to the updated const iterator.
     * @note Asserts if incremented while pointing to nullptr (end of the list).
     */
    ConstIterator& operator++();

    /**
     * @brief Increments the const iterator to the next node, returning the state before incrementation.
     * @return A copy of the const iterator before it was incremented.
     * @note Asserts if incremented while pointing to nullptr (end of the list).
     */
    ConstIterator operator++(int);

    /**
     * @brief Compares two const iterators for equality.
     * @param other Another const iterator to compare against.
     * @return True if both const iterators point to the same node, false otherwise.
     */
    bool operator==(ConstIterator const& other) const noexcept;

private:    
    const typename LinkedList<T>::Node* node_;

};

/**
 * @brief Compares two const iterators for inequality.
 * @param lhs Left-hand side const iterator to compare.
 * @param rhs Right-hand side const iterator to compare.
 * @return True if the const iterators do not point to the same node, false otherwise.
 */
template <typename T>
bool operator!=(ConstIterator<T> const& lhs, ConstIterator<T> const& rhs) noexcept;


template <typename T>
void reverse(LinkedList<T>& list) noexcept;

template <typename T>
LinkedList<T> flatten(LinkedList<LinkedList<T>>& list_of_lists);

template <typename T>
LinkedList<T> flatten(LinkedList<LinkedList<T>>&& list_of_lists);

} // namespace ds

#include "linked_list.inl"