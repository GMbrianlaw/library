namespace FenwickTree {

    template <typename P>
    auto forLevels(int size, P p) {

        auto index = 0;

        for (auto i = 31 - __builtin_clz(size); i >= 0; --i) {
            const auto new_index = index | 1 << i;
            if (new_index <= size && p(new_index)) {
                index = new_index;
            }
        }

        return index;

    }

    template <typename F>
    auto forParents(int node, int size, F f) {

        ++node;

        while (node <= size) {
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
