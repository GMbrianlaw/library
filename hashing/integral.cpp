#include <chrono>
#include <cstddef>

class IntegralHash {

public:

    template <typename T>
    auto operator()(T key) const {

        static const auto constant = static_cast<unsigned long long>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );

        auto result = static_cast<unsigned long long>(key);

        result += constant + 0x9e3779b97f4a7c15ll;
        result = (result ^ (result >> 30)) * 0xbf58476d1ce4e5b9ll;
        result = (result ^ (result >> 27)) * 0x94d049bb133111ebll;
        result ^= result >> 31;

        return static_cast<std::size_t>(result);

    }

};
