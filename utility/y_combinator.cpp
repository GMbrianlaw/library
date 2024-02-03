#include <utility>

template <typename F>
class YCombinator {

private:

    const F f = nullptr;

public:

    explicit YCombinator(F&& f) : f(f) {}

    template <typename... Ts>
    decltype(auto) operator()(Ts&&... arguments) const {

        return f(*this, std::forward<Ts>(arguments)...);

    }

};

template <typename F>
YCombinator(F) -> YCombinator<F>;
