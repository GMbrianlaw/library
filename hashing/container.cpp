#include <chrono>
#include <vector>

template <typename T>
class ContainerHasher {

private:

    static inline auto base = T(std::chrono::steady_clock::now().time_since_epoch().count());
    static inline auto powers = std::vector<T>({T(1)});

    std::vector<T> prefixes = std::vector<T>(1);

public:

    template <typename It>
    static auto hash(It first, It last) {

        auto result = T();

        while (first != last) {
            result = result * base + T(*first);
            ++first;
        }

        return result.value;

    }

    explicit ContainerHasher() = default;

    template <typename It>
    explicit ContainerHasher(It first, It last) {

        auto length = 0;

        while (first != last) {
            prefixes.push_back(prefixes.back() * base + T(*first));
            ++first;
            ++length;
        }

        powers.reserve(length + 1);

        while (static_cast<int>(powers.size()) <= length) {
            powers.push_back(powers.back() * base);
        }

    }

    auto pop() {

        prefixes.pop_back();

    }

    template <typename U>
    auto push(U value) {

        prefixes.push_back(prefixes.back() * base + T(value));

        if (powers.size() <= prefixes.size()) {
            powers.push_back(powers.back() * base);
        }

    }

    auto query(int index_1, int index_2) const {

        return (prefixes[index_2] - prefixes[index_1] * powers[index_2 - index_1]).value;

    }

};
