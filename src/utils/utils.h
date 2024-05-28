#pragma once

#include <stdexcept>

template<typename E, typename S>
class Either {
    E e;
    S s;

public:
    const bool isSuccess;

    Either(E e) : e(e), isSuccess(false) {}
    Either(S s) : s(s), isSuccess(true) {}

    [[nodiscard]] constexpr E getError() const {
        return !isSuccess ? e : throw std::logic_error("Assertion failed!");
    }
    [[nodiscard]] constexpr S getSuccess() const {
        return isSuccess ? s : throw std::logic_error("Assertion failed!");
    }
};