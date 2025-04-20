#pragma once

#include <functional>
#include <stack>
#include <cstddef>
#include <memory>

namespace dp {

/**
 * @brief A generic object pool that reuses allocated objects of type T.
 * @tparam T Object type to pool.
 * @tparam Factory Callable that returns std::unique_ptr<T>.
 */
template<typename T, typename Factory>
class ObjectPool {
public:
    explicit ObjectPool(size_t initial = 0);
    explicit ObjectPool(size_t initial, Factory fac);

    ~ObjectPool();

    ObjectPool(ObjectPool const&) = delete;
    ObjectPool& operator=(ObjectPool const&) = delete;
    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    std::unique_ptr<T> get() noexcept;
    void release(std::unique_ptr<T>&& p);

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
