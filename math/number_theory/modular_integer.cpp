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

template <int MODULUS_>
class ModularInteger {

private:

    static constexpr auto MODULUS = MODULUS_;

public:

    int value = 0;

    explicit ModularInteger() = default;

    explicit ModularInteger(long long value) : value(value % MODULUS) {

        if (this->value < 0) {
            this->value += MODULUS;
        }

    }

    auto operator-() const {

        return ModularInteger(-value);

    }

    auto operator++() {

        value = value < MODULUS - 1 ? value + 1 : 0;

    }

    auto operator--() {

        value = value ? value - 1 : MODULUS - 1;

    }

    auto operator+=(ModularInteger other) {

        if (other.value >= MODULUS - value) {
            value -= MODULUS;
        }

        value += other.value;

    }

    auto operator-=(ModularInteger other) {

        value -= other.value;

        if (value < 0) {
            value += MODULUS;
        }

    }

    auto operator*=(ModularInteger other) {

        value = static_cast<long long>(value) * other.value % MODULUS;

    }

    auto operator/=(ModularInteger other) {

        *this *= ModularInteger(extendedGCD(other.value, MODULUS)[1]);

    }

    friend auto operator+(ModularInteger lhs, ModularInteger rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(ModularInteger lhs, ModularInteger rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(ModularInteger lhs, ModularInteger rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(ModularInteger lhs, ModularInteger rhs) {

        lhs /= rhs;

        return lhs;

    }

};
