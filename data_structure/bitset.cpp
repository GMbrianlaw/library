#include <algorithm>
#include <vector>

class BitSet {

private:

    using BlockT = unsigned long long;

    int blocks = 0;
    std::vector<BlockT> data = std::vector<BlockT>();
    BlockT mask = 0;
    int sz = 0;

public:

    class Reference {

    private:

        BlockT& block;
        BlockT mask = 0;

    public:

        explicit Reference(BlockT& block, int bit) : block(block), mask(1llu << bit) {}

        operator bool() const {

            return block & mask;

        }

        auto operator=(bool x) {

            if (!x) {
                block &= ~mask;
            } else {
                block |= mask;
            }

        }

    };

    explicit BitSet(
        int size
    ) : blocks((size + 63) / 64), mask((size % 64 ? 1llu << size % 64 : 0) - 1), sz(size) {

        data.resize(blocks);

    }

    auto operator[](int pos) {

        return Reference(data[pos / 64], pos % 64);

    }

    auto operator[](int pos) const {

        return (data[pos / 64] & 1llu << pos % 64) != 0;

    }

    auto operator&=(const BitSet& other) {

        for (auto i = 0; i < blocks; ++i) {
            data[i] &= other.data[i];
        }

    }

    auto operator^=(const BitSet& other) {

        for (auto i = 0; i < blocks; ++i) {
            data[i] ^= other.data[i];
        }

    }

    auto operator|=(const BitSet& other) {

        for (auto i = 0; i < blocks; ++i) {
            data[i] |= other.data[i];
        }

    }

    auto all() const {

        for (auto i = 0; i < blocks - 1; ++i) {
            if (~data[i]) {
                return false;
            }
        }

        return (data[blocks - 1] & mask) == mask;

    }

    auto any() const {

        for (auto i = 0; i < blocks - 1; ++i) {
            if (data[i]) {
                return true;
            }
        }

        return (data[blocks - 1] & mask) != 0;

    }

    auto count() const {

        auto bits = __builtin_popcountll(data[blocks - 1] & mask);

        for (auto i = 0; i < blocks - 1; ++i) {
            bits += __builtin_popcountll(data[i]);
        }

        return bits;

    }

    auto flip() {

        for (auto& x : data) {
            x ^= ~0llu;
        }

    }

    auto reset() {

        std::fill(std::begin(data), std::end(data), 0);

    }

    auto set() {

        std::fill(std::begin(data), std::end(data), ~0llu);

    }

    auto size() const {

        return sz;

    }

    auto operator~() const {

        auto result = *this;

        result.flip();

        return result;

    }

    auto operator<<=(int pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        const auto bits = pos % 64;
        const auto shift = pos / 64;

        for (auto i = blocks - 1; i >= shift; --i) {
            data[i] = data[i - shift] << bits;
            if (bits && i > shift) {
                data[i] |= data[i - shift - 1] >> (64 - bits);
            }
        }

        std::fill_n(std::begin(data), shift, 0);

    }

    auto operator>>=(int pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        data[blocks - 1] &= mask;

        const auto bits = pos % 64;
        const auto shift = pos / 64;

        for (auto i = 0; i < blocks - shift; ++i) {
            data[i] = data[i + shift] >> bits;
            if (bits && i < blocks - shift - 1) {
                data[i] |= data[i + shift + 1] << (64 - bits);
            }
        }

        std::fill(std::end(data) - shift, std::end(data), 0);

    }

    auto none() const {

        return !any();

    }

    friend auto operator==(const BitSet& lhs, const BitSet& rhs) {

        const auto& data_1 = lhs.data;
        const auto& data_2 = rhs.data;
        const auto length = lhs.blocks;

        for (auto i = 0; i < length - 1; ++i) {
            if (data_1[i] != data_2[i]) {
                return false;
            }
        }

        return ((data_1[length - 1] ^ data_2[length - 1]) & lhs.mask) == 0;

    }

    friend auto operator&(BitSet lhs, const BitSet& rhs) {

        lhs &= rhs;

        return lhs;

    }

    friend auto operator^(BitSet lhs, const BitSet& rhs) {

        lhs ^= rhs;

        return lhs;

    }

    friend auto operator|(BitSet lhs, const BitSet& rhs) {

        lhs |= rhs;

        return lhs;

    }

    friend auto operator<<(BitSet lhs, int pos) {

        lhs <<= pos;

        return lhs;

    }

    friend auto operator>>(BitSet lhs, int pos) {

        lhs >>= pos;

        return lhs;

    }

    friend auto operator!=(const BitSet& lhs, const BitSet& rhs) {

        return !(lhs == rhs);

    }

};
