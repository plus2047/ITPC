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

int main() {
    lld N, flag;
    while (scanf("%lld", &N) != EOF) {
        vector<lld> C(N);
        for (int i = 0; i < N; i++) scanf("%lld", &C[i]);
        scanf("%lld", &flag);

        list<int> res;
        auto tail_iter = res.begin();
        lld tail_size = 0, tail_val = 0, cost = 0, front = -1;

        for (int i = 0; i < N; i++) {
            // printf("ts: %lld, tv: %lld\n", tail_size, tail_val);
            if (C[i] == 0) continue;
            int val = i + 1;
            if (front == -1) {
                front = val;
                tail_iter = res.insert(res.end(), C[i], val);
                tail_size = C[i];
                tail_val = val;
            } else if (val != tail_val + 1) {
                if (flag) {
                    while (tail_iter != res.end()) {
                        tail_iter++;
                        res.insert(tail_iter, tail_val + 1);
                        // cost++;
                    }
                    while (res.back() + 1 != val) {
                        res.push_back(res.back() + 1);
                        // cost++;
                    }
                    tail_iter = res.insert(res.end(), C[i], val);
                }
                cost += tail_size;
                cost += val - tail_val - 2;
                tail_size = C[i];
                tail_val = val;
            } else {  // val == tail_val + 1
                if (C[i] < tail_size) {
                    if (flag) {
                        while (next(tail_iter) != res.end()) {
                            tail_iter++;
                            res.insert(tail_iter, val);
                        }
                    }
                    cost += tail_size - 1 - C[i];
                    tail_size = 1;
                } else {
                    lld used = 0;
                    if (flag) {
                        while (next(tail_iter) != res.end()) {
                            tail_iter++;
                            res.insert(tail_iter, val);
                            // used++;
                        }
                    }
                    used += tail_size == 0 ? 0 : tail_size - 1;
                    if (abs(front - val) == 1 and used + 1 < C[i]) {
                        res.insert(res.begin(), val);
                        used++;
                        front = val;
                    }
                    tail_size = C[i] - used;
                    tail_val = val;
                    if (flag) {
                        for (int i = 0; i < tail_size; i++) {
                            res.push_back(val);
                            if (i == 0) tail_iter = prev(res.end());
                        }
                    }
                }
            }
        }
        if (tail_size > 1) {
            if (flag) {
                int insert_val = tail_val == 1 ? 2 : tail_val - 1;
                while (next(tail_iter) != res.end()) {
                    tail_iter++;
                    res.insert(tail_iter, insert_val);
                    // cost++;
                }
            }
            cost += tail_size - 1;
        }

        printf("%lld\n", cost);
        if (flag) {
            for (int x : res) {
                printf("%d ", x);
            }
            printf("\n");
        }
    }
}
