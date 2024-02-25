namespace FenwickTree {

    template <typename P>
    auto forLevels(int sz, P p) {

        auto idx = 0;

        for (auto i = 31 - __builtin_clz(sz); i >= 0; --i) {
            const auto new_idx = idx | 1 << i;
            if (new_idx <= sz && p(new_idx)) {
                idx = new_idx;
            }
        }

        return idx;

    }

    template <typename F>
    auto forParents(int node, int sz, F f) {

        ++node;

        while (node <= sz) {
            f(node);
            node += node & -node;
        }

    }

    template <typename F>
    auto forRange(int node, F f) {

        while (node) {
            f(node);
            node -= node & -node;
        }

    }

}
