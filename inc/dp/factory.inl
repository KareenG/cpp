#pragma once

#include "dp/factory.hpp"

namespace dp {

template<typename T>
std::unique_ptr<T> DefFactory<T>::create() 
{
    return std::make_unique<T>();
}

template<typename T>
RegFactory<T>::RegFactory(std::function<std::unique_ptr<T>()> func)
: func_(std::move(func))
{
}

template<typename T>
std::unique_ptr<T> RegFactory<T>::create()
{
    return func_();
}

} // namespace dp
