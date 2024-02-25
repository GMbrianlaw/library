template <typename T, typename U>
auto exponentiate(T base, U power, const T& id = T(1)) {

    auto res = id;

    while (power > 0) {
        if (power & 1) {
            res *= base;
        }
        base *= base;
        power >>= 1;
    }

    return res;

}
