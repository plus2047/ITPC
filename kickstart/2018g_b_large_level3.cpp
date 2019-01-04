// for programing contest
// never use int again (always use long long int)
#include <algorithm>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;

struct Point {
    lld index;
    int change;
    bool operator<(const Point& b) const {
        if (index != b.index)
            return index < b.index;
        else
            return change < b.change;
    }
};

#define MAX_N (400000 + 10)
#define MAX_Q (100000 + 10)
lld x[MAX_N], y[MAX_N], z[MAX_Q];
lld l[MAX_N], r[MAX_N], k[MAX_Q];

Point points[MAX_N * 2];
lld r_num[MAX_N * 2];
lld r_sum[MAX_N * 2];

int main() {
#ifdef __APPLE__
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        lld a[3], b[3], c[3], m[3], N, Q;
        scanf("%lld%lld", &N, &Q);
        scanf("%lld%lld%lld%lld%lld%lld", &x[0], &x[1], &a[0], &b[0], &c[0], &m[0]);
        scanf("%lld%lld%lld%lld%lld%lld", &y[0], &y[1], &a[1], &b[1], &c[1], &m[1]);
        scanf("%lld%lld%lld%lld%lld%lld", &z[0], &z[1], &a[2], &b[2], &c[2], &m[2]);
        for(int i = 0; i < N; i ++){
            if(i >= 2){
                x[i] = (a[0] * x[i - 1] + b[0] * x[i - 2] + c[0]) % m[0];
                y[i] = (a[1] * y[i - 1] + b[1] * y[i - 2] + c[1]) % m[1];
            }
            l[i] = min(x[i], y[i]) + 1;
            r[i] = max(x[i], y[i]) + 1;
        }
        for(int i = 0; i < Q; i ++){
            if(i >= 2){
                z[i] = (a[2] * z[i - 1] + b[2] * z[i - 2] + c[2]) % m[2];
            }
            k[i] = z[i] + 1;
        }
        // ===== solution begin =====
        for(int i = 0; i < N; i ++){
            points[2 * i].index = l[i]; points[2 * i].change = 1;
            points[2 * i + 1].index = r[i] + 1; points[2 * i + 1].change = -1;
        }
        sort(points, points + 2 * N);
        // for(int i = 0; i <= 2 * N; i ++){
        //     printf("point sorted: %lld %d\n", points[i].index, points[i].change);
        // }

        int pn = 0;
        // the last point is points[pn]
        for(int i = 1; i < 2 * N; i ++){
            if(points[i].index == points[i - 1].index){
                points[pn].change += points[i].change;
            }
            else{
                points[++pn] = points[i];
            }
        }
        // for(int i = 0; i <= pn; i ++){
        //     printf("point: %lld %d\n", points[i].index, points[i].change);
        // }

        // the last range depth is r_num[pn - 1]
        r_num[0] = points[0].change;
        for(int i = 1; i < pn; i ++){
            r_num[i] = r_num[i - 1] + points[i].change;
        }
        
        // the last range sum is r_sum[pn - 1]
        r_sum[0] = r_num[0] * (points[1].index - points[0].index);
        for(int i = 1; i < pn; i ++){
            r_sum[i] = r_sum[i - 1] + r_num[i] * (points[i + 1].index - points[i].index);
        }
        // for(int i = 0; i < pn; i ++){
        //     printf("r_num: %lld, r_sum: %lld\n", r_num[i], r_sum[i]);
        // }

        lld res = 0;
        for(int i = 0; i < Q; i ++){
            lld _k = r_sum[pn - 1] + 1 - k[i];
            if(_k <= 0) continue;
            // now 1 <= _k <= number of student

            int r_index = lower_bound(r_sum, r_sum + pn, _k) - r_sum;
            lld remain = r_index != 0 ? _k - r_sum[r_index - 1] : _k;
            lld s = points[r_index].index + (remain - 1) / r_num[r_index];

            // printf("r_index: %d, remain: %lld, s: %lld\n", r_index, remain, s);
            res +=  s * (i + 1);
        }
        printf("Case #%d: %lld\n", t, res);
        fprintf(stderr, "Case #%d: %lld\n", t, res);
    }
}
