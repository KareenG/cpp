#pragma once

#include "dp/object_pool.hpp"

namespace dp 
{

template<typename T, typename Factory>
ObjectPool<T, Factory>::ObjectPool(size_t initial)
: ObjectPool(initial, Factory())
{
}

template<typename T, typename Factory>
ObjectPool<T, Factory>::ObjectPool(size_t initial, Factory fac)
: initial_capacity_{initial}
, factory_{std::move(fac)} 
{
    for (size_t i = 0; i < initial; ++i) {
        storage_.push(factory_.create());
    }
}

template<typename T, typename Factory>
ObjectPool<T, Factory>::ObjectPool(size_t initial, size_t extra)
: ObjectPool(initial, extra, Factory())
{
}

template<typename T, typename Factory>
ObjectPool<T, Factory>::ObjectPool(size_t initial, size_t extra, Factory fac)
: initial_capacity_{initial}
, extra_capacity_{extra}
, factory_{std::move(fac)}
{
    for (size_t i = 0; i < initial; ++i) {
        storage_.push(factory_.create());
    }
}

template<typename T, typename Factory>
std::unique_ptr<T, PoolDeleter<T, Factory>> ObjectPool<T, Factory>::get() noexcept
{
    if (storage_.empty() && !grew_) {
        // Grow by extra capacity if allowed
        for (size_t i = 0; i < extra_capacity_; ++i) {
            storage_.push(factory_.create());
        }
        grew_ = true;
    }

    if (storage_.empty()) {
            return {nullptr, PoolDeleter<T, Factory>(this)};
    }
    auto raw = std::move(storage_.top());
    storage_.pop();

    return {raw.release(), PoolDeleter<T, Factory>(this)};
}

template<typename T, typename Factory>
void ObjectPool<T, Factory>::release(std::unique_ptr<T>&& p)
{
    if (p) {
        if (storage_.size() < initial_capacity_) {
            storage_.push(std::move(p));  // store only if under limit
        }
        // the object is destroyed (out of scope)
    }
}

template<typename T, typename Factory>
size_t ObjectPool<T, Factory>::size() const noexcept
{
    return initial_capacity_;
}

template<typename T, typename Factory>
size_t ObjectPool<T, Factory>::available() const noexcept
{
    return storage_.size();
}

template<typename T, typename Factory>
void ObjectPool<T, Factory>::reset()
{
    while (!storage_.empty()) {
        storage_.pop(); // destroys std::unique_ptr<T>
    }

    for (size_t i = 0; i < initial_capacity_ ; ++i) {
        storage_.push(factory_.create());
    }
    grew_ = false;
}

} // namespace dp