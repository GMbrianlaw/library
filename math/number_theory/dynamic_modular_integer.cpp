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

    static auto getModulus() {

        return modulus;

    }

    static auto setModulus(int modulus_) {

        modulus = modulus_;

    }

    int val = 0;

    explicit DynamicModularInteger() = default;

    explicit DynamicModularInteger(long long val) : val(val % modulus) {

        if (this->val < 0) {
            this->val += modulus;
        }

    }

    auto operator-() const {

        return DynamicModularInteger(-val);

    }

    auto operator++() {

        val = val < modulus - 1 ? val + 1 : 0;

    }

    auto operator--() {

        val = val ? val - 1 : modulus - 1;

    }

    auto operator+=(DynamicModularInteger other) {

        if (other.val >= modulus - val) {
            val -= modulus;
        }

        val += other.val;

    }

    auto operator-=(DynamicModularInteger other) {

        val -= other.val;

        if (val < 0) {
            val += modulus;
        }

    }

    auto operator*=(DynamicModularInteger other) {

        val = static_cast<long long>(val) * other.val % modulus;

    }

    auto operator/=(DynamicModularInteger other) {

        *this *= DynamicModularInteger(extendedGCD(other.val, modulus)[1]);

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
