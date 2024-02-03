#include <iterator>

namespace FunctionContainer {

    template <typename T, typename F>
    auto erase(typename T::iterator it, T& cont, F f) {

        while (
            it != cont.begin() && std::prev(it) != cont.begin() &&
            f(*std::prev(it), *it) <= f(*std::prev(it, 2), *std::prev(it))
        ) {
            it = cont.erase(prev(it));
        }

        while (
            it != std::prev(cont.end()) && it != std::prev(cont.end(), 2) &&
            f(*it, *std::next(it)) >= f(*std::next(it), *std::next(it, 2))
        ) {
            it = std::prev(cont.erase(std::next(it)));
        }

    }

}
