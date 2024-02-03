#include <array>
#include <utility>

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
class ModularCongruence {

public:

    T a = T();
    T m = T(1);

    explicit ModularCongruence() = default;

    explicit ModularCongruence(T a, T m) : a(a), m(m) {}

    auto operator&=(ModularCongruence other) {

        const auto [other_a, other_m] = other;

        const auto [divisor, coef_m, coef_n] = extendedGCD(m, other_m);

        if ((a - other_a) % divisor) {
            a = 0;
            m = 0;
            return;
        }

        const auto multiple = m / divisor * other_m;

        a = (a + coef_m * (other_a - a) / divisor % (other_m / divisor) * m) % multiple;
        m = multiple;

        if (a < 0) {
            a += m;
        }

    }

    friend auto operator&(ModularCongruence lhs, ModularCongruence rhs) {

        lhs &= rhs;

        return lhs;

    }

};
