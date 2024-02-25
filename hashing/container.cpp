#include <chrono>
#include <vector>

template <typename T>
class ContainerHasher {

private:

    static inline auto base = T(std::chrono::steady_clock::now().time_since_epoch().count());
    static inline auto pows = std::vector<T>({T(1)});

    std::vector<T> pfxs = std::vector<T>(1);

public:

    template <typename It>
    static auto hash(It it_l, It it_r) {

        auto res = T();

        while (it_l != it_r) {
            res = res * base + T(*it_l);
            ++it_l;
        }

        return res.val;

    }

    explicit ContainerHasher() = default;

    template <typename It>
    explicit ContainerHasher(It it_l, It it_r) {

        while (it_l != it_r) {
            pfxs.push_back(pfxs.back() * base + T(*it_l));
            ++it_l;
        }

        const auto len = it_r - it_l;

        pows.reserve(len + 1);

        while (static_cast<int>(pows.size()) <= len) {
            pows.push_back(pows.back() * base);
        }

    }

    auto pop() {

        pfxs.pop_back();

    }

    template <typename U>
    auto push(U val) {

        pfxs.push_back(pfxs.back() * base + T(val));

        if (pows.size() <= pfxs.size()) {
            pows.push_back(pows.back() * base);
        }

    }

    auto query(int idx_1, int idx_2) const {

        return (pfxs[idx_2] - pfxs[idx_1] * pows[idx_2 - idx_1]).val;

    }

};
