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

int main() {
    int T;
    scanf("%d", &T);
    int h[128];
    for (int t = 0; t < T; t++) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++) scanf("%d", &h[i]);
        int pos = -1;
        while(k) {
            int _pos = -1;
            for(int i = 0; i < n; i++) {
                if(i + 1 < n and h[i] < h[i + 1]) {
                    h[i]++;
                    _pos = i;
                    break;
                }
            }
            pos = _pos;
            if(_pos != -1) {
                k--;
            } else {
                break;
            }
        }
        printf("%d\n", pos == -1 ? pos : pos + 1);
    }
}
