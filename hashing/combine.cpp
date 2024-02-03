#include <cstddef>

auto combineHash(std::size_t hash, std::size_t seed) {

    seed ^= hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;

}
