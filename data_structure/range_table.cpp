namespace RangeTable {

    auto log2(int x) {

        return 31 - __builtin_clz(x);

    }

    template <typename F>
    auto forAll(int size, F f) {

        for (auto i = 0; i < size; ++i) {
            f(0, i, true);
        }

        for (auto i = 1; i <= log2(size); ++i) {
            for (auto j = 0; j < size >> i; ++j) {
                const auto sz = 1 << (i - 1);
                for (auto k = 1; k <= sz; ++k) {
                    f(i, sz * (j << 1 | 1) - k, k == 1);
                }
                for (auto k = 0; k < sz; ++k) {
                    f(i, sz * (j << 1 | 1) + k, k == 0);
                }
            }
        }

    }

    template <typename F>
    auto forRange(int index_1, int index_2, F f) {

        --index_2;

        if (index_1 == index_2) {
            f(0, index_1);
            return;
        }

        const auto level = log2(index_1 ^ index_2) + 1;

        f(level, index_1);
        f(level, index_2);

    }

}
