#pragma once

#include <vector>
#include <utility>  // For std::move
#include <stdexcept> // For std::runtime_error

namespace ds {

template <class T>
struct Node {
public:
    /**
     * @brief Constructs a new node with given data and next node pointer.
     *
     * This constructor initializes a node of the linked list with user-provided data
     * and a pointer to the next node in the list, defaulting to nullptr if no next
     * node is specified.
     *
     * @param data The data to store in this node.
     * @param next Pointer to the next node in the list, or nullptr if none.
     */
    Node(const T& data, Node<T>* next = nullptr)
    : data_(data)
    , next_(next) 
    {
    }

public:
    T data_;
    Node<T>* next_;
};


template <class T>
class LinkedList {

public:
     /**
     * @brief Default constructor that initializes an empty LinkedList.
     *
     * Sets up an initially empty list with the head pointer set to nullptr and the
     * size of the list set to zero.
     */
    LinkedList()
    : head_(nullptr)
    , size_{}
    {
    }

    /**
     * @brief Destructor that clears the linked list.
     *
     * Cleans up all nodes in the list, ensuring no memory leak occurs.
     */
    ~LinkedList()
    {
        clear(); 
    }

    /**
     * @brief Constructs a LinkedList from a vector of elements.
     *
     * This constructor creates a new linked list and populates it with elements from
     * a given vector. Each element from the vector is used to create a new node in the
     * linked list.
     *
     * @param vec A constant reference to a vector containing elements to be added to the list.
     */
    LinkedList(std::vector<T> const& vec)
    : head_(nullptr)
    , size_{}
    {
        build_list(vec);
    }

    /**
     * @brief Constructs a LinkedList from a vector of elements using move semantics.
     *
     * This constructor efficiently moves elements from a given vector into the new linked list,
     * minimizing copying and memory allocation overhead.
     *
     * @param vec An rvalue reference to a vector containing elements to be moved into the list.
     */
    LinkedList<T>(std::vector<T>&& vec)
    : head_(nullptr)
    , size_{}
    {
        build_list(vec);
    }

    /**
     * @brief Copy constructor that duplicates another LinkedList.
     *
     * Creates a new linked list as a deep copy of an existing one, ensuring that all nodes
     * are newly allocated with the same data as in the original list.
     *
     * @param other The LinkedList to be copied.
     */
    LinkedList<T>(LinkedList<T> const& other)
    : head_(nullptr)
    , size_(other.size_)
    {
        if (other.head_ == nullptr) {
            return;
        }

        head_ = new Node<T>(other.head_->data_);
        Node<T>* current = head_;
        Node<T>* current_other = other.head_->next_;

        while (current_other != nullptr) {
            current->next_ = new Node<T>(current_other->data_);
            current = current->next_;
            current_other = current_other->next_;
        }
    }

    /**
     * @brief Move constructor that initializes the LinkedList with the contents of another list.
     *
     * Efficiently transfers the nodes from another LinkedList to this one, leaving the other
     * list in a valid but empty state.
     *
     * @param other Another LinkedList object to move data from.
     */
    LinkedList(LinkedList&& other) noexcept
    : head_(other.head_)
    , size_(other.size_) 
    {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    /**
     * @brief Returns the number of elements in the linked list.
     *
     * @return The size of the linked list as a size_t.
     */
    size_t size()
    {
        return size_;
    }

    /**
     * @brief Move assignment operator that transfers the contents of another list to this one.
     *
     * Clears the current list, then transfers the contents of another list,
     * leaving the other list empty.
     *
     * @param other Another LinkedList to assign to this one.
     * @return Reference to this LinkedList after assignment.
     */
    LinkedList& operator=(LinkedList&& other) noexcept 
    {
        if (this != &other) {
            clear();
            head_ = other.head_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Copy assignment operator that duplicates the contents of another list to this one.
     *
     * Ensures deep copy is performed when assigning from another list.
     *
     * @param other A constant reference to another LinkedList to copy from.
     * @return Reference to this LinkedList after copy assignment.
     */
    LinkedList<T>& operator=(LinkedList<T> const& other) {
        if (this != &other) {
            LinkedList<T> temp(other);
            std::swap(head_, temp.head_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    /**
     * @brief Inserts an element at the beginning of the list.
     *
     * This method creates a new node with the given element and adds it at the start
     * of the list, pushing other elements back.
     *
     * @param element The element to insert at the front of the list.
     */
    void push(T const& element)
    {
        Node<T>* new_node = new Node<T>(element, head_);
        head_ = new_node;
        size_++;
    }

    /**
     * @brief Inserts an element at the beginning of the list using move semantics.
     *
     * This method creates a new node with the given moved element and adds it at the start
     * of the list, efficiently transferring the element into the list.
     *
     * @param element An rvalue reference to the element to be moved to the front of the list.
     */
    void push(T&& element)
    {
        Node<T>* new_node = new Node<T>(std::move(element), head_);
        head_ = new_node;
        size_++;
    }

    /**
     * @brief Removes the element at the beginning of the list and returns it.
     *
     * If the list is empty, throws a std::runtime_error. Otherwise, removes the head element,
     * returns its value, and reduces the size of the list by one.
     *
     * @return The data stored in the head element of the list.
     * @throws std::runtime_error if the list is empty.
     */
    T pop() 
    {
        if (head_ == nullptr) {
            throw std::runtime_error("Attempt to pop from an empty list.");
        }
    
        Node<T>* nodeToPop = head_;
        T data = nodeToPop->data_;
        head_ = head_->next_;
        delete nodeToPop;
        --size_;
    
        return data;
    }
    
private:
    void build_list(std::vector<T>&& vec) {
        for (int i = vec.size() - 1; i >= 0; --i) {
            head_ = new Node<T>(std::move(vec[i]), head_);
        }
        size_ = vec.size();
    }

    void build_list(std::vector<T> const& vec) {
        for (int i = vec.size() - 1; i >= 0; --i) {
            head_ = new Node<T>(vec[i], head_);
        }
        size_ = vec.size();
    }

    void clear() 
    {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next_;
            delete current;
            current = next;
        }
        head_ = nullptr;
        size_ = 0;  
    }

private: 
    Node<T>* head_;
    size_t size_;
};

} // namespace ds