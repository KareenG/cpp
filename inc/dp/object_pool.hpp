#pragma once

#include <functional>
#include <stack>
#include <cstddef>
#include <memory>

#include "dp/factory.hpp"
#include "dp/pool_deleter.hpp"

namespace dp {

template<typename T, typename Factory = DefHeapAllocatingFactory<T>>
class PoolDeleter;

/**
 * @brief A generic object pool that manages reusable objects of type T.
 * 
 * This pool allocates and stores a number of reusable objects to reduce
 * allocation overhead. It supports dynamic growth and automatically returns
 * objects to the pool via a custom deleter.
 * 
 * @tparam T The type of object managed by the pool.
 * @tparam Factory A type providing `std::unique_ptr<T> create()` to instantiate objects.
 * 
 * @details
 * - initial_capacity_: The maximum number of idle objects retained.
 * - extra_capacity_: Number of temporary objects allowed beyond the initial pool.
 * - extra_available_: Tracks remaining dynamic allocations allowed.
 * - factory_: Responsible for creating new instances of `T`.
 * - storage_: Internal LIFO stack of available objects.
 */
template<typename T, typename Factory = DefHeapAllocatingFactory<T>>
class ObjectPool {
public:
    /**
     * @brief Constructs a pool with a fixed number of pre-allocated objects.
     * 
     * @param initial Number of objects to pre-allocate and retain.
     * @param fac Factory used to construct each object (default-constructed if not provided).
     */
    explicit ObjectPool(size_t initial = 0, Factory fac = Factory());

    /**
     * @brief Constructs a dynamically growing pool with extra capacity.
     * 
     * @param initial Number of objects to pre-allocate and retain.
     * @param extra Maximum number of additional objects to create on demand.
     * @param fac Factory used to construct each object.
     */
    explicit ObjectPool(size_t initial, size_t extra, Factory fac = Factory());

    /**
     * @brief Destructor that releases all owned objects.
     */
    ~ObjectPool() noexcept = default;

    ObjectPool(ObjectPool const&) = delete;
    ObjectPool& operator=(ObjectPool const&) = delete;
    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    /**
     * @brief Acquires an object from the pool.
     * 
     * If the pool is exhausted and dynamic growth is allowed, a temporary object
     * will be created. All returned objects are wrapped in a `unique_ptr` with
     * a custom deleter to return them to the pool automatically.
     * 
     * @return A unique_ptr to an object, or nullptr if allocation is not possible.
     */
    std::unique_ptr<T, PoolDeleter<T, Factory>> get();

    /**
     * @brief Returns the number of objects the pool retains when idle.
     */
    size_t size() const noexcept;

    /**
     * @brief Returns the number of currently available (idle) objects in the pool.
     */
    size_t available() const noexcept;

private:
    friend PoolDeleter<T, Factory>;

    /**
     * @brief Returns an object to the pool.
     * 
     * If the pool is full (i.e., already holds the initial capacity), the object is destroyed.
     * 
     * @param p The object to return.
     * 
     * @note This is called by the `PoolDeleter`. Do not call it manually.
     */
    void release(std::unique_ptr<T>&& p);

    /**
     * @brief Destroys all current pool contents and resets to the initial capacity.
     */
    void reset();

private:
    size_t initial_capacity_;
    size_t extra_capacity_;
    size_t extra_available_;
    Factory factory_;
    std::stack<std::unique_ptr<T>> storage_;
};

} // namespace dp

#include "dp/object_pool.inl"
