#pragma once

#include "dp/pool_deleter.hpp"

namespace dp {

template<typename T, typename Factory>
class ObjectPool; // Forward declare

template<typename T, typename Factory>
PoolDeleter<T, Factory>::PoolDeleter(ObjectPool<T, Factory>* pool) noexcept
: pool_(pool)
{
}

template<typename T, typename Factory>
void PoolDeleter<T, Factory>::operator()(T* ptr) const noexcept
{
    if (pool_ && ptr) {
        pool_->release(std::unique_ptr<T>(ptr));
    }
}

} // namespace dp
