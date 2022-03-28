#ifndef TILO_FORWARD_HPP
#define TILO_FORWARD_HPP

#include <type_traits>

namespace te {
    template <class T>
    [[nodiscard]] inline constexpr T&& forward(std::remove_reference_t<T>& val) noexcept {
        return static_cast<T&&>(val);
    }

    template <class T>
    [[nodiscard]] inline constexpr T&& forward(std::remove_reference_t<T>&& val) noexcept {
        static_assert(!std::is_lvalue_reference_v<T>, "Bad forward call! Value must be a lvalue reference!");
        return static_cast<T&&>(val);
    }
}

#endif