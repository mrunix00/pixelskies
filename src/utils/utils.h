#pragma once

template<typename E, typename S>
class Either {
    bool success;

public:
    Either(E e) : e(e), success(false) {}
    Either(S s) : s(s), success(true) {}

    [[nodiscard]] constexpr bool isSuccessful() const { return success; }
    [[nodiscard]] constexpr bool isFailed() const { return !success; }

    [[nodiscard]] constexpr E getError() const { return e; }
    [[nodiscard]] constexpr S getSuccess() const { return s; }

    E e;
    S s;
};