#include "mu_test.h"
#include "dp/object_pool.hpp"

#include <string>
#include <memory>

struct Dummy {
    int val = 0;
    explicit Dummy(int v = 0)
    : val(v) 
    {
    }
};

// BEGIN_TEST(construction_and_get)
//     dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(3);

//     ASSERT_EQUAL(pool.size(), 3);
//     ASSERT_EQUAL(pool.available(), 3);

//     auto a = pool.get();
//     ASSERT_THAT(a.get());
//     ASSERT_EQUAL(pool.available(), 2);

//     auto b = pool.get();
//     ASSERT_EQUAL(pool.available(), 1);

//     auto c = pool.get();
//     ASSERT_EQUAL(pool.available(), 0);

//     auto d = pool.get();  // allocates new object since pool is empty
//     ASSERT_THAT(d.get());
//     ASSERT_EQUAL(pool.available(), 0); // still 0, nothing was returned
// END_TEST

// BEGIN_TEST(release_and_reuse)
//     dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(1);

//     auto obj = pool.get();
//     ASSERT_EQUAL(pool.available(), 0);

//     pool.release(std::move(obj));
//     ASSERT_EQUAL(pool.available(), 1);

//     auto reused = pool.get();
//     ASSERT_THAT(reused.get());
//     ASSERT_EQUAL(pool.available(), 0);
// END_TEST

// BEGIN_TEST(release_null_is_ignored)
//     dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(0);

//     std::unique_ptr<Dummy> null_ptr;
//     pool.release(std::move(null_ptr));

//     ASSERT_EQUAL(pool.available(), 0);
// END_TEST

/*------------------------------------------------------------------------------------------*/

// BEGIN_TEST(released_automatically)
//     dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(3);

//     ASSERT_EQUAL(pool.size(), 3);
//     ASSERT_EQUAL(pool.available(), 3);
    
//     {
//         auto a = pool.get();
//         auto b = pool.get();
//         auto c = pool.get();
//         auto d = pool.get();  // causes a new object to be allocated
//         ASSERT_THAT(a.get());
//         //ASSERT_THAT(a != nullptr);
//         ASSERT_THAT(b.get());
//         ASSERT_THAT(c.get());
//         ASSERT_THAT(!d.get());
//         ASSERT_EQUAL(pool.available(), 0); // nothing was returned yet
//     } // <-- All 3 objects go out of scope here and are automatically returned

//     ASSERT_EQUAL(pool.available(), 3);  // 3 objects returned to pool
// END_TEST

// BEGIN_TEST(reset_behavior)
//     dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(2);

//     ASSERT_EQUAL(pool.available(), 2);

//     auto a = pool.get();
//     auto b = pool.get();

//     ASSERT_EQUAL(pool.available(), 0);

//     pool.reset();

//     ASSERT_EQUAL(pool.available(), 2);
// END_TEST

/*---------------------------------------------------------------------------------*/

BEGIN_TEST(feature2_test)
    dp::ObjectPool<int> pool(3);
    ASSERT_EQUAL(pool.size(), 3);
    ASSERT_EQUAL(pool.available(),3);
    {
    auto obj1 = pool.get();
    auto obj2 = pool.get();
    auto obj3 = pool.get();
    ASSERT_EQUAL(pool.available(),0);

    }
    ASSERT_EQUAL(pool.available(),3);
END_TEST

BEGIN_TEST(feature2_with_factory)
    // Define a factory that creates Dummy objects with value 77
    auto factory = dp::Factory<Dummy>([] {
        return std::make_unique<Dummy>(77);
    });

    // Create a pool using this factory
    dp::ObjectPool<Dummy, dp::Factory<Dummy>> pool(2, factory);

    ASSERT_EQUAL(pool.size(), 2);
    ASSERT_EQUAL(pool.available(), 2);

    auto obj1 = pool.get();
    auto obj2 = pool.get();
    ASSERT_THAT(obj1.get());
    ASSERT_THAT(obj2.get());
    ASSERT_EQUAL(obj1->val, 77);
    ASSERT_EQUAL(obj2->val, 77);

    // Should return nullptr since pool is exhausted
    auto obj3 = pool.get();
    ASSERT_THAT(obj3 == nullptr);
    ASSERT_EQUAL(pool.available(), 0);
END_TEST

/*---------------------------------------------------------------------------------*/

BEGIN_TEST(dynamic_growth_and_limit_check)
    // Pool starts with 2, can grow by 3 more
    dp::ObjectPool<Dummy> pool(2, 3);

    ASSERT_EQUAL(pool.size(), 2);
    ASSERT_EQUAL(pool.available(), 2);

    auto obj1 = pool.get();
    auto obj2 = pool.get();
    auto obj3 = pool.get(); // triggers growth
    auto obj4 = pool.get();
    auto obj5 = pool.get();

    ASSERT_THAT(obj1.get());
    ASSERT_THAT(obj2.get());
    ASSERT_THAT(obj3.get());
    ASSERT_THAT(obj4.get());
    ASSERT_THAT(obj5.get());

    // Exceeds initial + extra → should return nullptr
    auto obj6 = pool.get();
    ASSERT_THAT(obj6 == nullptr);
    ASSERT_EQUAL(pool.available(), 0);
END_TEST

BEGIN_TEST(dynamic_release_discards_excess)
    dp::ObjectPool<Dummy> pool(2, 2);

    {
        // Lease 4 objects (2 + 2 overflow)
        auto obj1 = pool.get();
        auto obj2 = pool.get();
        auto obj3 = pool.get();
        auto obj4 = pool.get();
        ASSERT_EQUAL(pool.available(), 0);
    }

    ASSERT_EQUAL(pool.available(), 2); // No more than initial capacity
END_TEST

BEGIN_TEST(dynamic_auto_release_only_keeps_initial)
    dp::ObjectPool<Dummy> pool(2, 2);

    {
        auto a = pool.get();
        auto b = pool.get();
        auto c = pool.get(); // extra
        auto d = pool.get(); // extra
        ASSERT_THAT(a.get());
        ASSERT_THAT(b.get());
        ASSERT_THAT(c.get());
        ASSERT_THAT(d.get());
    } // All 4 released automatically (via PoolDeleter)

    // Only initial_capacity_ retained
    ASSERT_EQUAL(pool.available(), 2);
END_TEST

BEGIN_SUITE(ObjectPool_BasicTests)
    // feature 1
    // TEST(construction_and_get)
    // TEST(release_and_reuse)
    // TEST(release_null_is_ignored)

    // feature 2
    // TEST(released_automatically)
    // TEST(reset_behavior)

    // feature 3
    TEST(feature2_test)
    TEST(feature2_with_factory)

    // feature 4
    TEST(dynamic_growth_and_limit_check)
    TEST(dynamic_release_discards_excess)
    TEST(dynamic_auto_release_only_keeps_initial)

END_SUITE
