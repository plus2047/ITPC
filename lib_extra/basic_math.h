#include <limits>
#include <random>

namespace contest {

template <typename num>
struct RandNum {
    std::mt19937 gen;
    std::uniform_int_distribution<num> dist;

    RandNum(num left, num right, unsigned seed = 0)
        : gen(seed), dist(left, right) {}

    num operator()() { return dist(gen); }
};

RandNum<int> get_rand_int = RandNum<int>(0, std::numeric_limits<int>::max());

// float calculate.
// always using double. if necessary, using long double.

const double DELTA = 1E-9;

inline int sign(double x) { return (x > DELTA) - (x < -DELTA); }

// return 1 if x > y; 0 if abs(x - y) < DELTA; -1 if x < y
inline int compare(double x1, double x2) { return sign(x1 - x2); }

}  // namespace contest