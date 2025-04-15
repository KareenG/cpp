#pragma once

#include <cstddef>

#include "linked_list.hpp"

namespace ds
{
    
template <typename T>
struct LinkedList<T>::Node {
    T data_;
    Node* next_;

    Node(const T& data, Node* next = nullptr);
    Node(T&& data, Node* next = nullptr);
};

template <typename T>
LinkedList<T>::Node::Node(const T& data, Node* next)
: data_{data}
, next_{next}
{
}

template <typename T>
LinkedList<T>::Node::Node(T&& data, Node* next)
: data_{std::move(data)}
, next_{next}
{
}

template <typename T>
LinkedList<T>::LinkedList()
: head_{nullptr}
, size_{}
{
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept {
    clear(head_);
    size_ = 0;
}

template <typename T>
LinkedList<T>::LinkedList(std::vector<T>const& vec)
: head_{initialize_list(vec)}
{
}

template <typename T>
LinkedList<T>::LinkedList(std::vector<T>&& vec)
: head_{initialize_list(vec)}
{
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
: head_{other.head_}
, size_{other.size_} 
{
    other.head_ = nullptr;
    other.size_ = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept 
{
    clear(head_);
    head_ = std::exchange(other.head_, nullptr);
    size_ = std::exchange(other.size_, 0);
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> const& other)
{
    if (this != &other) {
        LinkedList<T> temp(other);

        using std::swap;
        swap(head_, temp.head_);
        swap(size_, temp.size_);
    }
    return *this;
}

template <typename T>
void LinkedList<T>::push(T const& element)
{
    head_ = new Node(element, head_);
    ++size_;
}

template <typename T>
void LinkedList<T>::push(T&& element)
{
    head_ = new Node(std::move(element), head_);
    ++size_;
}

template <typename T>
void LinkedList<T>::pop(T& pop_data) 
{
    assert(size_ > 0);

    pop_data = std::move(head_->data_);
    Node* node_to_pop = head_;
    head_ = head_->next_;
    delete node_to_pop;
    --size_;
}

template <typename T>
size_t LinkedList<T>::size() const noexcept
{
    return size_;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& other)
{
    using std::swap;
    swap(head_, other.head_);
    swap(size_, other.size_);
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::initialize_list(const std::vector<T>& vec) {
    Node* local_head = nullptr;
    size_ = vec.size();
    try {
        for (int i = vec.size() - 1; i >= 0; --i) {
            local_head = new Node(vec[i], local_head);
        }
        size_ = vec.size();
    } catch(...) {
        clear(local_head);
        size_ = 0;
    }
    return local_head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::initialize_list(const std::vector<T>&& vec) {
    Node* local_head = nullptr;
    size_ = vec.size();
    try {
        for (int i = vec.size() - 1; i >= 0; --i) {
            local_head = new Node(std::move(vec[i]), local_head);
        }
        size_ = vec.size();
    } catch(...) {
        clear(local_head);
        size_ = 0;
    }
    return local_head;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
: head_{initialize_list_from_other(other)}
//, size_{other.size_}
{
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::initialize_list_from_other(const LinkedList& other) {
    if (other.size_ == 0) {
        return nullptr;
    }
    size_ = other.size_;
    Node* head = nullptr;
    Node* current = nullptr;
    try {
        head = new Node(other.head_->data_);
        current = head;
        Node* otherCurrent = other.head_->next_;

        while (otherCurrent != nullptr) {
            current->next_ = new Node(otherCurrent->data_);
            current = current->next_;
            otherCurrent = otherCurrent->next_;
        }
    } catch (...) {
        clear(head);
        size_ = 0;
    }
    return head;
}

template <typename T>
void LinkedList<T>::clear(Node* start) {
    while (start != nullptr) {
        Node* next = start->next_;
        delete start;
        start = next;
    }
}

template <typename T>
bool LinkedList<T>::empty() {
    return size_ == 0;
}


/*-------------------------------------------------------------------------------------*/


template <typename T>
Iterator<T>::Iterator(typename LinkedList<T>::Node* node)
: node_{node}
{
}

template <typename T>
Iterator<T> LinkedList<T>::begin() noexcept {
    return Iterator<T>{head_};
}

template <typename T>
Iterator<T> LinkedList<T>::end() noexcept {
    return Iterator<T>{nullptr};
}

template <typename T>
T const& Iterator<T>::operator*() const {
    assert(node_ != nullptr);
    return node_->data_;
}

// Prefix increment
template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
}

// Postfix increment - return the state of the iterator before it was incremented.
template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    assert(node_ != nullptr);
    Iterator tmp = *this;
    node_ = node_->next_;
    return tmp;
}

template <typename T>
bool Iterator<T>::operator==(Iterator const& other) const noexcept {
    return node_ == other.node_;
}

template <typename T>
bool operator!=(Iterator<T> const& lhs, Iterator<T> const& rhs) noexcept {
    return !(lhs == rhs);
}


/*-------------------------------------------------------------------------------------*/


template <typename T>
ConstIterator<T>::ConstIterator(const typename LinkedList<T>::Node* node)
: node_{node}
{
}

template <typename T>
ConstIterator<T> LinkedList<T>::cbegin() const noexcept {
    return ConstIterator<T>{head_};
}

template <typename T>
ConstIterator<T> LinkedList<T>::cend() const noexcept {
    return ConstIterator<T>{nullptr};
}

template <typename T>
ConstIterator<T> LinkedList<T>::begin() const noexcept {
    return cbegin();
}

template <typename T>
ConstIterator<T> LinkedList<T>::end() const noexcept {
    return cend();
}

template <typename T>
T const& ConstIterator<T>::operator*() const {
    assert(node_ != nullptr);
    return node_->data_;
}

// Prefix increment
template <typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
}

// Postfix increment - return the state of the iterator before it was incremented.
template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    assert(node_ != nullptr);
    ConstIterator tmp = *this;
    node_ = node_->next_;
    return tmp;
}

template <typename T>
bool ConstIterator<T>::operator==(ConstIterator const& other) const noexcept {
    return node_ == other.node_;
}

template <typename T>
bool operator!=(ConstIterator<T> const& lhs, ConstIterator<T> const& rhs) noexcept {
    return !(lhs == rhs);
}

// Handles both cases (whether the list is an lvalue or an rvalue)
template <typename T>
void reverse(LinkedList<T>& list) noexcept {
    // LinkedList<T> temp;
    // for (Iterator<T> it = list.begin(); it != list.end(); ++it) {
    //     temp.push_front(std::move(*it));
    // }
    // list = std::move(temp);

    LinkedList<T> reversed;
    // Using iterator to access each element from the original list
    for (Iterator<T> it = list.begin(); it != list.end(); ++it) {
        // If LinkedList supports push_front, use it to reverse the elements
        reversed.push(std::move(*it)); // Assuming push_front is a member function
    }
    // Replace the original list with the reversed one
    list = std::move(reversed);
}

template<typename T>
LinkedList<T> flatten(const ds::LinkedList<ds::LinkedList<T>>& list_of_lists)
{
    LinkedList<T> flattened;
    for(const LinkedList<T>& sublist : list_of_lists) {
        for(const T& item : sublist) {
            flattened.push(item);  // Copies each item
        }
    }
    return flattened;

    // LinkedList<T> flattened;
    // // Iterate over each sublist using a const_iterator
    // for (Iterator<LinkedList<T>> outer_it = list_of_lists.begin(); outer_it != list_of_lists.end(); ++outer_it) {
    //     const ds::LinkedList<T>& sublist = *outer_it;
    //     // Use iterator to go through each element in the sublist
    //     for (Iterator<T> inner_it = sublist.begin(); inner_it != sublist.end(); ++inner_it) {
    //         const T& item = *inner_it;
    //         flattened.push(item);  // Copies each item
    //     }
    // }
    // return flattened;
}


template <typename T>
LinkedList<T> flatten(LinkedList<LinkedList<T>>&& list_of_lists) {
    LinkedList<T> flattened;
    for (LinkedList& sublist : list_of_lists) {
        while (!sublist.empty()) {
            T element;
            sublist.pop(element);
            flattened.push(std::move(element));
        }
    }
    return flattened;
}

} // namespace ds
