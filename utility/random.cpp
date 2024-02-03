#include <chrono>
#include <random>

namespace Random {

    auto rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

}
