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

template <int>
class DynamicModularInteger {

private:

    static inline auto modulus = 0;

public:

    static auto setModulus(int modulus_) {

        modulus = modulus_;

    }

    int value = 0;

    explicit DynamicModularInteger() = default;

    explicit DynamicModularInteger(long long value) : value(value % modulus) {

        if (this->value < 0) {
            this->value += modulus;
        }

    }

    auto operator-() const {

        return DynamicModularInteger(-value);

    }

    auto operator++() {

        value = value < modulus - 1 ? value + 1 : 0;

    }

    auto operator--() {

        value = value ? value - 1 : modulus - 1;

    }

    auto operator+=(DynamicModularInteger other) {

        if (other.value >= modulus - value) {
            value -= modulus;
        }

        value += other.value;

    }

    auto operator-=(DynamicModularInteger other) {

        value -= other.value;

        if (value < 0) {
            value += modulus;
        }

    }

    auto operator*=(DynamicModularInteger other) {

        value = static_cast<long long>(value) * other.value % modulus;

    }

    auto operator/=(DynamicModularInteger other) {

        *this *= DynamicModularInteger(extendedGCD(other.value, modulus)[1]);

    }

    friend auto operator+(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs /= rhs;

        return lhs;

    }

};
