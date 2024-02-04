#include <numeric>
#include <utility>
#include <vector>

class DisjointSetUnion {

private:

    std::vector<int> reps = std::vector<int>();
    std::vector<int> sizes = std::vector<int>();

public:

    explicit DisjointSetUnion(int size) {

        reps.resize(size);

        std::iota(reps.begin(), reps.end(), 0);

        sizes.assign(size, 1);

    }

    auto find(int node) {

        auto ptr = node;

        while (reps[ptr] != ptr) {
            ptr = reps[ptr];
        }

        const auto parent = ptr;

        ptr = node;

        while (ptr != parent) {
            const auto next = reps[ptr];
            reps[ptr] = parent;
            ptr = next;
        }

        return parent;

    }

    auto getSize(int node) {

        return sizes[find(node)];

    }

    auto merge(int node_1, int node_2) {

        node_1 = find(node_1);
        node_2 = find(node_2);

        if (node_1 != node_2) {
            if (sizes[node_1] < sizes[node_2]) {
                std::swap(node_1, node_2);
            }
            reps[node_2] = node_1;
            sizes[node_1] += sizes[node_2];
        }

    }

};
