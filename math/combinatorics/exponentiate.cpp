template <typename T, typename U>
auto exponentiate(T base, U power, const T& identity = T(1)) {

    auto result = identity;

    while (power > 0) {
        if (power & 1) {
            result *= base;
        }
        base *= base;
        power >>= 1;
    }

    return result;

}
