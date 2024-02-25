#include <chrono>
#include <cstddef>

class IntegralHash {

public:

    template <typename T>
    auto operator()(T key) const {

        static const auto constant = static_cast<unsigned long long>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );

        auto res = static_cast<unsigned long long>(key);

        res += constant + 0x9e3779b97f4a7c15ll;
        res = (res ^ (res >> 30)) * 0xbf58476d1ce4e5b9ll;
        res = (res ^ (res >> 27)) * 0x94d049bb133111ebll;
        res ^= res >> 31;

        return static_cast<std::size_t>(res);

    }

};
