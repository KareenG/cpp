#include "mu_test.h"
#include "dp/object_pool.hpp"

#include <string>
#include <memory>

struct Dummy {
    int val = 0;
    explicit Dummy(int v = 0) : val(v) {}
};

BEGIN_TEST(construction_and_get)
    dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(3);

    ASSERT_EQUAL(pool.size(), 3);
    ASSERT_EQUAL(pool.available(), 3);

    auto a = pool.get();
    ASSERT_THAT(a.get());
    ASSERT_EQUAL(pool.available(), 2);

    auto b = pool.get();
    ASSERT_EQUAL(pool.available(), 1);

    auto c = pool.get();
    ASSERT_EQUAL(pool.available(), 0);

    auto d = pool.get();  // allocates new object since pool is empty
    ASSERT_THAT(d.get());
    ASSERT_EQUAL(pool.available(), 0); // still 0, nothing was returned
END_TEST

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

BEGIN_TEST(release_null_is_ignored)
    dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(0);

    std::unique_ptr<Dummy> null_ptr;
    pool.release(std::move(null_ptr));

    ASSERT_EQUAL(pool.available(), 0);
END_TEST

BEGIN_TEST(released_automatically)
    dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(3);

    ASSERT_EQUAL(pool.size(), 3);
    ASSERT_EQUAL(pool.available(), 3);
    
    {
        auto a = pool.get();
        auto b = pool.get();
        auto c = pool.get();
        auto d = pool.get();  // causes a new object to be allocated
        ASSERT_THAT(a.get());
        //ASSERT_THAT(a != nullptr);
        ASSERT_THAT(b.get());
        ASSERT_THAT(c.get());
        ASSERT_THAT(!d.get());
        ASSERT_EQUAL(pool.available(), 0); // nothing was returned yet
    } // <-- All 3 objects go out of scope here and are automatically returned

    ASSERT_EQUAL(pool.available(), 3);  // 3 objects returned to pool
END_TEST

BEGIN_TEST(reset_behavior)
    dp::ObjectPool<Dummy, std::function<std::unique_ptr<Dummy>()>> pool(2);

    ASSERT_EQUAL(pool.available(), 2);

    auto a = pool.get();
    auto b = pool.get();

    ASSERT_EQUAL(pool.available(), 0);

    pool.reset();

    ASSERT_EQUAL(pool.available(), 2);
END_TEST


BEGIN_SUITE(ObjectPool_BasicTests)
    // TEST(construction_and_get)
    // TEST(release_and_reuse)
    // TEST(release_null_is_ignored)
    TEST(released_automatically)
    TEST(reset_behavior)
END_SUITE
