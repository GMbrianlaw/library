namespace SegmentTree {

    template <typename P>
    auto forLevels(int node, int size, bool direction, P p) {

        while (node < size) {
            node = node << 1 | direction + (!direction ? p(node) : -p(node));
        }

        return node;

    }

    template <typename F>
    auto forRange(int node_1, int node_2, F f) {

        while (node_1 < node_2) {
            if (node_1 & 1) {
                f(node_1);
                ++node_1;
            }
            if (node_2 & 1) {
                --node_2;
                f(node_2);
            }
            node_1 >>= 1;
            node_2 >>= 1;
        }

    }

    auto log2(int x) {

        return 31 - __builtin_clz(x);

    }

    template <typename F>
    auto forParents(int node, bool direction, F f) {

        const auto levels = log2(node);

        for (auto i = 1; i <= levels; ++i) {
            f(node >> (!direction ? levels - i + 1 : i));
        }

    }

    template <typename F>
    auto forRangeOrdered(int node_1, int node_2, bool direction, F f) {

        auto base = !direction ? node_1 - 1 : node_2;
        const auto mask = (1 << log2((node_1 - 1) ^ node_2)) - 1;
        const auto offset = !direction ? 1 : -1;

        auto node = (!direction ? -node_1 : node_2) & mask;

        while (node) {
            const auto bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }

        base = direction ? node_1 - 1 : node_2;
        node = (direction ? -node_1 : node_2) & mask;

        while (node) {
            const auto bit = log2(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }

    }

}
