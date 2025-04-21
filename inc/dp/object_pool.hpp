#pragma once

#include <functional>
#include <stack>
#include <cstddef>
#include <memory>

#include "dp/factory.hpp"
#include "dp/pool_deleter.hpp"

namespace dp {

template<typename T, typename Factory = Factory<T>>
class PoolDeleter;

/**
 * @brief A generic object pool that manages reusable objects of type T.
 * 
 * The pool creates an initial number of objects and allows clients to acquire
 * and release them. Optionally, the pool can grow dynamically to serve more
 * clients than initially allocated. Dynamically created objects are discarded
 * once returned if the pool already holds its initial capacity.
 * 
 * @tparam T The type of objects managed by the pool.
 * @tparam Factory A factory type that provides `std::unique_ptr<T> create()`.
 * 
 * @details
 * Member variables:
 * - initial_capacity_: The maximum number of objects that the pool will retain internally.
 *   This defines the size of the pool when idle.
 * - extra_capacity_: The number of additional objects to allocate when the pool runs out
 *   of available objects. These extras are not retained when returned.
 * - factory_: The factory used to construct new objects. It must provide a `create()` method
 *   returning `std::unique_ptr<T>`.
 * - storage_: A stack-based container holding the currently available (idle) objects.
 * - grew_: A flag that indicates whether the pool has already grown dynamically once. Used
 *   to enforce single-growth semantics if desired.
 */
template<typename T, typename Factory = Factory<T>>
class ObjectPool {
public:
    /**
     * @brief Constructs a pool with an initial number of objects using the default factory.
     * @param initial Number of objects to pre-allocate.
     */
    explicit ObjectPool(size_t initial = 0);

    /**
     * @brief Constructs a pool with an initial number of objects using a custom factory.
     * @param initial Number of objects to pre-allocate.
     * @param fac Factory object used to create objects.
     */
    explicit ObjectPool(size_t initial, Factory fac);

    /**
     * @brief Constructs a dynamic pool with initial and extra capacity using the default factory.
     * @param initial Number of objects to pre-allocate.
     * @param extra Number of objects to create on-demand when exhausted.
     */
    explicit ObjectPool(size_t initial, size_t extra);

    /**
     * @brief Constructs a dynamic pool with initial and extra capacity using a custom factory.
     * @param initial Number of objects to pre-allocate.
     * @param extra Number of objects to create on-demand when exhausted.
     * @param fac Factory object used to create objects.
     */
    explicit ObjectPool(size_t initial, size_t extra, Factory fac);

    /**
     * @brief Destroys the pool and all objects it holds.
     */
    ~ObjectPool() noexcept = default;

    ObjectPool(ObjectPool const&) = delete;
    ObjectPool& operator=(ObjectPool const&) = delete;
    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    /**
     * @brief Acquires an object from the pool.
     * 
     * If the pool is exhausted, it will grow by the extra capacity if allowed.
     * Returned objects are automatically returned to the pool when their
     * unique_ptr goes out of scope (via a custom deleter).
     * 
     * @return A unique_ptr to an object, or nullptr if no object can be provided.
     */
    std::unique_ptr<T, PoolDeleter<T, Factory>> get() noexcept;

    /**
     * @brief Returns the number of objects the pool retains at idle (initial capacity).
     */
    size_t size() const noexcept;

    /**
     * @brief Returns the number of objects currently available in the pool.
     */
    size_t available() const noexcept;

    
private:

    friend PoolDeleter<T, Factory>;

    /**
     * @brief Called by the custom deleter to return the object to the pool.
     * @note This overload is internal — users should not call it directly.
     * @param p The object to return.
     */
    //void release(std::unique_ptr<T, PoolDeleter<T, Factory>>&& p);

    /**
     * @brief Manually returns an object to the pool.
     * 
     * If the pool is already full (based on initial capacity), the object is discarded.
     * 
     * @param p The object to return.
     */
    void release(std::unique_ptr<T>&& p);

    /**
     * @brief Resets the pool, destroying all objects and reinitializing to the original size.
     */
    void reset();

private:
    size_t initial_capacity_;
    size_t extra_capacity_ = 0;
    Factory factory_;
    std::stack<std::unique_ptr<T>> storage_;
    bool grew_ = false;
};

} // namespace dp

#include "dp/object_pool.inl"
