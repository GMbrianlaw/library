#include <vector>

template <typename It>
auto prefixFunction(It it_l, It it_r) {

    const auto sz = it_r - it_l;

    auto pfx_vals = std::vector<int>(sz);

    for (auto i = 1; i < sz; ++i) {
        auto& len = pfx_vals[i];
        len = pfx_vals[i - 1];
        const auto& val = it_l[i];
        while (len && val != it_l[len]) {
            len = pfx_vals[len - 1];
        }
        len += it_l[len] == val;
    }

    return pfx_vals;

}
