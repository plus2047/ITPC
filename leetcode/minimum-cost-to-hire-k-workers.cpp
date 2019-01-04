// for programing contest
#include <algorithm>
#include <cfloat>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "lib/leetcode_io.h"

#define __DEBUG__
#ifdef __DEBUG__
#include "lib/show.h"
#endif  // __DEBUG__

using namespace std;
using namespace contest;

typedef long long int lld;
typedef long long unsigned llu;

template <typename TUPLE, size_t FIELD>
bool upper(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) > std::get<FIELD>(b);
}
template <typename TUPLE, size_t FIELD>
bool lower(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) < std::get<FIELD>(b);
}

class Solution {
   public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage,
                                int K) {
        int N = quality.size();

        typedef tuple<int, double> Worker;
        const size_t q_ = 0, r_ = 1;

        vector<Worker> workers(N);
        for (int i = 0; i < N; i++) {
            workers[i] = {quality[i], 1.0 * wage[i] / quality[i]};
        }

        // sort by rate
        sort(workers.begin(), workers.end(), lower<Worker, r_>);

        auto begin = workers.begin();
        int curr_quality = 0;
        for (int i = 0; i < K; i++) {
            curr_quality += get<q_>(workers[i]);
        }
        double min_sum = get<r_>(workers[K - 1]) * curr_quality;

        // make max heap by quality
        make_heap(begin, begin + K, lower<Worker, q_>);
        for (int i = K; i < N; i++) {
            curr_quality += get<q_>(workers[i]) - get<q_>(workers[0]);
            min_sum = min(min_sum, curr_quality * get<r_>(workers[i]));

            pop_heap(begin, begin + K, lower<Worker, q_>);
            workers[K - 1] = workers[i];
            push_heap(begin, begin + K, lower<Worker, q_>);
        }

        return min_sum;
    }
};

int main() {
#ifdef __DEBUG__
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    vector<int> quality = get_vector<int>();
    vector<int> wage = get_vector<int>();
    int K = get_num<int>();
    Solution sol;
    cout << sol.mincostToHireWorkers(quality, wage, K) << endl;
}

// [10,20,5]
// [70,50,30]
// 2

// [32,43,66,9,94,57,25,44,99,19]
// [187,366,117,363,121,494,348,382,385,262]
// 4