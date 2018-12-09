// for programing contest
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <random>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <map>
#include <stdexcept>

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;


int main() {
    #ifdef __APPLE__
    freopen("_in_large.txt", "r", stdin);
    freopen("_out_cpp.txt", "w", stdout);
    #endif

    llu T; scanf("%llu", &T);
    for(llu t = 1; t <= T; t ++){
        llu N; scanf("%llu", &N);
        string _in; cin >> _in;

        llu len = (N + 1) / 2, score = 0, win_sum = 0;
        for(int i = 0; i < N; i ++){
            win_sum += _in[i] - '0';
            if(i >= len - 1){
                score = max(score, win_sum);
                win_sum -= _in[i - (len - 1)] - '0';
            }
        }

        printf("Case #%llu: %llu\n", t, score);
    }
}
