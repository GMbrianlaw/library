#include <vector>

namespace Sieve {

    auto factors = std::vector<int>();
    auto primes = std::vector<int>();

    auto reserve(int size) {

        factors.resize(size + 1);

        for (auto i = 2; i <= size; ++i) {
            if (factors[i] == 0) {
                factors[i] = i;
                primes.push_back(i);
            }
            for (auto x : primes) {
                if (i * x > size) {
                    break;
                }
                factors[i * x] = x;
                if (x == factors[i]) {
                    break;
                }
            }
        }

    }

}
