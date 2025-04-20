#pragma once

#include "dp/factory.hpp"

namespace dp {

template<typename T>
Factory<T>::Factory(std::function<std::unique_ptr<T>()> func)
: func_(std::move(func))
{
}

template<typename T>
std::unique_ptr<T> Factory<T>::create() const
{
    return func_();
}

} // namespace dp
