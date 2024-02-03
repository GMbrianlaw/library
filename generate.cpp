#include <chrono>
#include <random>

namespace Random {

    auto rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

}

template <typename T>
auto nextInt(T a, T b) {

    return std::uniform_int_distribution<T>(a, b - 1)(Random::rng);

}

auto nextBool() {

    return static_cast<bool>(nextInt(0, 2) & 1);

}

auto nextChar(bool upper) {

    return static_cast<char>(nextInt(0, 26) + (!upper ? 'a' : 'A'));

}
