#include <algorithm>
#include <array>
#include <cstdlib>
#include <utility>

template <typename T>
auto boundDiophantine(T x, T y, T shift_x, T shift_y, T min_x, T max_x, T min_y, T max_y) {

    const auto shift = [&](T amount) {
        x += shift_x * amount;
        y -= shift_y * amount;
    };

    shift((min_x - x) / shift_x);

    const auto sign_a = shift_x > 0 ? 1 : -1;

    if (x < min_x) {
        shift(sign_a);
    }

    const auto empty_range = std::array<T, 3>();

    if (x > max_x) {
        return empty_range;
    }

    const auto x_1 = x;

    shift((max_x - x) / shift_x);

    if (x > max_x) {
        shift(-sign_a);
    }

    const auto x_2 = x;

    shift((y - min_y) / shift_y);

    const auto sign_b = shift_y > 0 ? 1 : -1;

    if (y < min_y) {
        shift(-sign_b);
    }

    if (y > max_y) {
        return empty_range;
    }

    auto x_3 = x;

    shift((y - max_y) / shift_y);

    if (y > max_y) {
        shift(sign_b);
    }

    if (x_3 > x) {
        std::swap(x_3, x);
    }

    const auto x_high = std::min(x_2, x);
    const auto x_low = std::max(x_1, x_3);

    if (x_low > x_high) {
        return empty_range;
    }

    return std::array<T, 3>({x_low, x_high, (x_high - x_low) / std::abs(shift_x) + 1});

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
