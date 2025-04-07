#include <iostream>
#include <vector>

#include "mu_test.h"

#include "ds/linked_list.hpp"

BEGIN_TEST(test_default_constructor)
    ds::LinkedList<int> list;
    ASSERT_EQUAL(list.size(), 0);
END_TEST

BEGIN_TEST(test_vector_constructor)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> list(vec);
    ASSERT_EQUAL(list.size(), 3);
END_TEST

BEGIN_TEST(test_copy_constructor)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> original(vec);
    ds::LinkedList<int> copy(original);
    ASSERT_EQUAL(copy.size(), original.size());
    ASSERT_THAT(&copy != &original);
END_TEST

BEGIN_TEST(test_move_constructor)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> original(vec);
    ds::LinkedList<int> moved(std::move(original));
    ASSERT_EQUAL(moved.size(), 3);
    ASSERT_EQUAL(original.size(), 0);
END_TEST

// BEGIN_TEST(test_clear)
//     std::vector<int> vec = {1, 2, 3};
//     ds::LinkedList<int> list(vec);
//     list.clear();
//     ASSERT_EQUAL(list.size(), 0);
// END_TEST

BEGIN_TEST(test_push_lvalue)
    ds::LinkedList<int> list;
    int value = 4;
    list.push(value);
    ASSERT_EQUAL(list.size(), 1);
END_TEST

BEGIN_TEST(test_push_rvalue)
    ds::LinkedList<int> list;
    list.push(5);
    ASSERT_EQUAL(list.size(), 1);
END_TEST

BEGIN_TEST(test_pop_empty)
    std::vector<int> vec = {};
    ds::LinkedList<int> list(vec);
    try {
        list.pop();
        std::cout << "No exception thrown when expected" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected std::runtime_error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Caught unexpected exception type" << std::endl;
    }
    
    ASSERT_EQUAL(0, list.size());
END_TEST

BEGIN_TEST(test_pop_one_elem_vec)
    std::vector<int> vec = {1};
    ds::LinkedList<int> list(vec);
    ASSERT_EQUAL(list.pop(), 1);
    ASSERT_EQUAL(list.size(), 0);
END_TEST

BEGIN_TEST(test_pop)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> list(vec);
    ASSERT_EQUAL(list.pop(), 1);
    ASSERT_EQUAL(list.size(), 2);
END_TEST

BEGIN_TEST(test_copy_assignment_operator)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> original(vec);
    ds::LinkedList<int> copy;
    copy = original;
    ASSERT_EQUAL(copy.size(), original.size());
END_TEST

BEGIN_TEST(test_move_assignment_operator)
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> original(vec);
    ds::LinkedList<int> moved;
    moved = std::move(original);   
    ASSERT_EQUAL(moved.size(), 3);
    ASSERT_EQUAL(original.size(), 0); 
END_TEST

TEST_SUITE()
    TEST(test_default_constructor)
    TEST(test_vector_constructor)
    TEST(test_copy_constructor)
    TEST(test_move_constructor)
    TEST(test_push_lvalue)
    TEST(test_push_rvalue)
    TEST(test_pop_empty) 
    TEST(test_pop_one_elem_vec)
    TEST(test_pop)
    TEST(test_copy_assignment_operator)
    TEST(test_move_assignment_operator)
END_SUITE
