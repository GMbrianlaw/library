#include <vector>

template <typename T>
class Combinatorics {

private:

    std::vector<T> factorials = std::vector<T>();
    std::vector<T> inv_factorials = std::vector<T>();
    int reached = 0;

public:

    auto reserve(int size) {

        if (reached == 0) {
            factorials.emplace_back(1);
            inv_factorials.emplace_back(1);
            reached = 1;
        }

        if (size < reached) {
            return;
        }

        const auto sz = 1 << (31 - __builtin_clz(size * 2 - 1));

        factorials.resize(sz + 1);
        inv_factorials.resize(sz + 1);

        for (auto i = reached; i <= sz; ++i) {
            factorials[i] = factorials[i - 1] * T(i);
        }

        inv_factorials[sz] = T(1) / factorials[sz];

        for (auto i = sz - 1; i >= reached; --i) {
            inv_factorials[i] = inv_factorials[i + 1] * T(i + 1);
        }

        reached = sz + 1;

    }

    auto combine(int n, int k) {

        reserve(n);

        return factorials[n] * inv_factorials[k] * inv_factorials[n - k];

    }

    auto getFact(int n) {

        reserve(n);

        return factorials[n];

    }

    auto getInv(int n) {

        reserve(n);

        return inv_factorials[n] * factorials[n - 1];

    }

    auto getInvFact(int n) {

        reserve(n);

        return inv_factorials[n];

    }

    auto permute(int n, int k) {

        reserve(n);

        return factorials[n] * inv_factorials[n - k];

    }

};
