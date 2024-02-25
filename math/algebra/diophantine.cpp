#include <algorithm>
#include <array>
#include <cstdlib>
#include <utility>

template <typename T>
auto boundDiophantine(T x, T y, T shift_x, T shift_y, T mn_x, T mx_x, T mn_y, T mx_y) {

    const auto shift = [&](T amount) {
        x += shift_x * amount;
        y -= shift_y * amount;
    };

    shift((mn_x - x) / shift_x);

    const auto sign_a = shift_x > 0 ? 1 : -1;

    if (x < mn_x) {
        shift(sign_a);
    }

    const auto empty_range = std::array<T, 3>();

    if (x > mx_x) {
        return empty_range;
    }

    const auto x_1 = x;

    shift((mx_x - x) / shift_x);

    if (x > mx_x) {
        shift(-sign_a);
    }

    const auto x_2 = x;

    shift((y - mn_y) / shift_y);

    const auto sign_b = shift_y > 0 ? 1 : -1;

    if (y < mn_y) {
        shift(-sign_b);
    }

    if (y > mx_y) {
        return empty_range;
    }

    auto x_3 = x;

    shift((y - mx_y) / shift_y);

    if (y > mx_y) {
        shift(sign_b);
    }

    if (x_3 > x) {
        std::swap(x_3, x);
    }

    const auto x_hi = std::min(x_2, x);
    const auto x_lo = std::max(x_1, x_3);

    if (x_lo > x_hi) {
        return empty_range;
    }

    return std::array<T, 3>({x_lo, x_hi, (x_hi - x_lo) / std::abs(shift_x) + 1});

}

template <typename T>
auto extendedGCD(T m, T n) {

    auto a = T(1);
    auto a_inner = T();
    auto b = T();
    auto b_inner = T(1);

    while (n) {
        const auto q = m / n;
        a_inner = std::exchange(a, a_inner) - q * a_inner;
        b_inner = std::exchange(b, b_inner) - q * b_inner;
        n = std::exchange(m, n) - q * n;
    }

    return std::array<T, 3>({m, a, b});

}

template <typename T>
auto diophantine(T a, T b, T c) {

    if (a == 0 && b == 0) {
        return std::array<T, 3>({0, 0, c == 0 ? 3 : 0});
    }

    auto [divisor, x, y] = extendedGCD(std::abs(a), std::abs(b));

    if (c % divisor) {
        return std::array<T, 3>();
    }

    x *= c / divisor;
    y *= c / divisor;

    if (a < 0) {
        x = -x;
    }

    if (b < 0) {
        y = -y;
    }

    return std::array<T, 3>({x, y, a && b ? 1 : 2});

}
