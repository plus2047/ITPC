#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long int lld;

struct Group {
    int type, start;
    lld count;
    Group(int t, int s, lld c) : type(t), start(s), count(c) {}
};

int main() {
    for (int N, Q; scanf("%d%d", &N, &Q) != EOF;) {
        vector<lld> popu(N);
        deque<Group> deq;  // <type, startTime, count>
        char s[32];
        lld c, t, k;
        for (int i = 0; i < Q; i++) {
            scanf("%s%lld%lld%lld", s, &c, &t, &k);
            t--;
            c += k;

            if (s[0] == 'f') {
                while (k) {
                    auto& g = deq.front();
                    if (g.count <= k) {
                        popu[g.type] += lld(i - g.start) * g.count;
                        k -= g.count;
                        deq.pop_front();
                    } else {
                        g.count -= k;
                        popu[g.type] += lld(i - g.start) * k;
                        k = 0;
                    }
                }
                deq.push_front(Group(t, i, c));
            } else {
                while (k) {
                    auto& g = deq.back();
                    if (g.count <= k) {
                        popu[g.type] += lld(i - g.start) * g.count;
                        k -= g.count;
                        deq.pop_back();
                    } else {
                        popu[g.type] += lld(i - g.start) * k;
                        g.count -= k;
                        k = 0;
                    }
                }
                deq.push_back(Group(t, i, c));
            }
        }
        while (deq.size()) {
            auto g = deq.back();
            deq.pop_back();
            popu[g.type] += lld(Q - g.start) * g.count;
        }
        for (int i = 0; i < N; i++) {
            printf("%lld ", popu[i]);
        }
        printf("\n");
    }
}
