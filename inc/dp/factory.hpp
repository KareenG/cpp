#pragma once

#include <memory>
#include <functional>

namespace dp {

/**
 * @brief Default factory that creates objects using make_unique<T>().
 */
template<typename T>
class DefFactory {
public:
    std::unique_ptr<T> create();
};

/**
 * @brief User-specified factory wrapper using std::function.
 */
template<typename T>
class RegFactory {
public:
    explicit RegFactory(std::function<std::unique_ptr<T>()> func = [] {
        return std::make_unique<T>();
    });

    std::unique_ptr<T> create();

private:
    std::function<std::unique_ptr<T>()> func_;
};

} // namespace dp

#include "dp/factory.inl"