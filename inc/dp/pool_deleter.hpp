#pragma once

#include <memory>

namespace dp {

template <typename T, typename Factory>
class ObjectPool;

/**
 * @brief Custom deleter that returns a unique_ptr<T> to its originating pool.
 * Used by ObjectPool when returning objects via get().
 *
 * @tparam T Object type.
 * @tparam Factory Factory type used by the ObjectPool.
 */
template <typename T, typename Factory>
class PoolDeleter {
public:
    /**
     * @brief Constructs a deleter associated with a specific pool.
     * @param pool Pointer to the object pool that owns the objects.
     */
    explicit PoolDeleter(ObjectPool<T, Factory>* pool) noexcept;

    /**
     * @brief Called by unique_ptr<T, PoolDeleter> on destruction.
     *        Returns the raw pointer back to the pool.
     * @param ptr The pointer to delete (actually returned to the pool).
     */
    void operator()(T* ptr) const noexcept;

private:
    // Owning pool, used to return the object.
    ObjectPool<T, Factory>* pool_; 
};

} // namespace dp

#include "dp/pool_deleter.inl"