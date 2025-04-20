#pragma once

#include <functional>
#include <stack>
#include <cstddef>
#include <memory>

#include "dp/factory.hpp"
#include "dp/pool_deleter.hpp"

namespace dp {

// template<typename T>
// class PoolDeleter;

template<typename T>
class DefFactory;

template<typename T>
class RegFactory;

/**
 * @brief A generic object pool that reuses allocated objects of type T.
 * @tparam T Object type to pool.
 * @tparam Factory Callable that returns std::unique_ptr<T>.
 */
template<typename T, typename Factory = DefFactory<T>>
class ObjectPool {
public:
    // static_assert(
    //     std::is_same<
    //         std::unique_ptr<T>,
    //         decltype(std::declval<Factory>().create())
    //     >::value,
    //     "Factory must have a create() method returning std::unique_ptr<T>"
    // );
    

    explicit ObjectPool(size_t initial = 0);
    explicit ObjectPool(size_t initial, Factory fac);

    ~ObjectPool();

    ObjectPool(ObjectPool const&) = delete;
    ObjectPool& operator=(ObjectPool const&) = delete;
    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    std::unique_ptr<T, PoolDeleter<T, Factory>> get() noexcept;
    void release(std::unique_ptr<T>&& p);

    void release(std::unique_ptr<T, PoolDeleter<T, Factory>>&& p);


    size_t size() const noexcept;
    size_t available() const noexcept;
    void reset();

private:
    size_t initial_capacity_;
    Factory factory_;
    std::stack<std::unique_ptr<T>> storage_;
};

} // namespace dp

#include "dp/object_pool.inl"
