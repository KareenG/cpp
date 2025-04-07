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

// SHOULD FAIL
BEGIN_TEST(test_pop_empty)
    std::vector<int> vec = {};
    ds::LinkedList<int> list(vec);
    int popped{};
    list.pop(popped);
END_TEST

BEGIN_TEST(test_pop_one_elem_vec)
    std::vector<int> vec = {1};
    ds::LinkedList<int> list(vec);
    int popped{0};
    list.pop(popped);
    ASSERT_EQUAL(popped, 1);
    ASSERT_EQUAL(list.size(), 0);
END_TEST

BEGIN_TEST(test_pop)  
    std::vector<int> vec = {1, 2, 3};
    ds::LinkedList<int> list(vec);
    int popped{};
    for(int i = 1; i <= 3; ++i) {
        list.pop(popped);
        ASSERT_EQUAL(popped, i);
        ASSERT_EQUAL(list.size(),static_cast<size_t>(3 - i));
    }
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

/*-------------------------------------------------------------*/

BEGIN_TEST(test_iterator_dereference)
    std::vector<int> vec = {10, 20, 30};
    ds::LinkedList<int> list(vec);
    ds::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 10);
END_TEST

BEGIN_TEST(test_iterator_prefix_increment)
    std::vector<int> vec = {10, 20, 30};
    ds::LinkedList<int> list(vec);
    ds::Iterator it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 20);
END_TEST

BEGIN_TEST(test_iterator_postfix_increment)
    std::vector<int> vec = {10, 20, 30};
    ds::LinkedList<int> list(vec);
    ds::Iterator it = list.begin();
    ds::Iterator old_it = it++;
    ASSERT_EQUAL(*old_it, 10);
    ASSERT_EQUAL(*it, 20);
END_TEST

BEGIN_TEST(test_iterator_equality)
    std::vector<int> vec = {10, 20, 30};
    ds::LinkedList<int> list(vec);
    ds::Iterator it1 = list.begin();
    ds::Iterator it2 = list.begin();
    ASSERT_THAT(it1 == it2);
END_TEST

BEGIN_TEST(test_iterator_inequality)
    std::vector<int> vec = {10, 20, 30};
    ds::LinkedList<int> list(vec);
    ds::Iterator it1 = list.begin();
    ds::Iterator it2 = list.begin();
    ++it2;
    ASSERT_THAT(it1 != it2);
END_TEST

/*-------------------------------------------------------------*/

BEGIN_TEST(test_const_iterator_dereference)
    std::vector<int> vec = {10, 20, 30};
    const ds::LinkedList<int> list(vec);
    ds::ConstIterator it = list.cbegin();
    ASSERT_EQUAL(*it, 10);
END_TEST

BEGIN_TEST(test_const_iterator_prefix_increment)
    std::vector<int> vec = {10, 20, 30};
    const ds::LinkedList<int> list(vec);
    ds::ConstIterator it = list.cbegin();
    ++it;
    ASSERT_EQUAL(*it, 20);
END_TEST

BEGIN_TEST(test_const_iterator_postfix_increment)
    std::vector<int> vec = {10, 20, 30};
    const ds::LinkedList<int> list(vec);
    ds::ConstIterator it = list.cbegin();
    ds::ConstIterator old_it = it++;
    ASSERT_EQUAL(*old_it, 10);
    ASSERT_EQUAL(*it, 20);
END_TEST

BEGIN_TEST(test_const_iterator_equality)
    std::vector<int> vec = {10, 20, 30};
    const ds::LinkedList<int> list(vec);
    ds::ConstIterator it1 = list.cbegin();
    ds::ConstIterator it2 = list.cbegin();
    ASSERT_THAT(it1 == it2);
END_TEST

BEGIN_TEST(test_const_iterator_inequality)
    std::vector<int> vec = {10, 20, 30};
    const ds::LinkedList<int> list(vec);
    ds::ConstIterator it1 = list.cbegin();
    ds::ConstIterator it2 = list.cbegin();
    ++it2;
    ASSERT_THAT(it1 != it2);
END_TEST


/*-------------------------------------------------------------*/

TEST_SUITE()
    TEST(test_default_constructor)
    TEST(test_vector_constructor)
    TEST(test_copy_constructor)
    TEST(test_move_constructor)
    TEST(test_push_lvalue)
    TEST(test_push_rvalue)
    //TEST(test_pop_empty) 
    TEST(test_pop_one_elem_vec)
    TEST(test_pop)
    TEST(test_copy_assignment_operator)
    TEST(test_move_assignment_operator)


    TEST(test_iterator_dereference)
    TEST(test_iterator_prefix_increment)
    TEST(test_iterator_postfix_increment)
    TEST(test_iterator_equality)
    TEST(test_iterator_inequality)


    TEST(test_const_iterator_dereference)
    TEST(test_const_iterator_prefix_increment)
    TEST(test_const_iterator_postfix_increment)
    TEST(test_const_iterator_equality)
    TEST(test_const_iterator_inequality)

END_SUITE
