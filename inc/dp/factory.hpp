#pragma once

#include <memory>
#include <functional>

namespace dp {

/**
 * @brief A generic DefHeapAllocatingFactory that creates objects of type T using std::unique_ptr.
 * 
 * This DefHeapAllocatingFactory defaults to using `std::make_unique<T>()`, but can also wrap 
 * a user-supplied function to create objects with custom constructors or logic.
 * 
 * @tparam T The type of object to create.
 */
template<typename T>
class DefHeapAllocatingFactory {
public:
    /**
     * @brief Constructs a default DefHeapAllocatingFactory that uses `std::make_unique<T>()`.
     */
    DefHeapAllocatingFactory() = default;

    ~DefHeapAllocatingFactory() noexcept = default;
    DefHeapAllocatingFactory(const DefHeapAllocatingFactory&) = default;
    DefHeapAllocatingFactory(DefHeapAllocatingFactory&&) noexcept = default;
    DefHeapAllocatingFactory& operator=(const DefHeapAllocatingFactory&) = default;
    DefHeapAllocatingFactory& operator=(DefHeapAllocatingFactory&&) noexcept = default;

    /**
     * @brief Constructs a DefHeapAllocatingFactory with a user-defined object creation function.
     * 
     * @param func A callable that returns a `std::unique_ptr<T>`.
     */
    explicit DefHeapAllocatingFactory(std::function<std::unique_ptr<T>()> func);

    /**
     * @brief Creates a new object using the stored creation function.
     * 
     * @return A `std::unique_ptr<T>` to the newly created object.
     */
    std::unique_ptr<T> create() const;

private:
    /**
     * @brief The function used to create new objects.
     * Defaults to `[] { return std::make_unique<T>(); }`.
     */
    std::function<std::unique_ptr<T>()> func_ = [] {
        return std::make_unique<T>();
    };
};

} // namespace dp

#include "dp/factory.inl"
