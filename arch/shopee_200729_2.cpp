// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11

using namespace std;

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// ========== contest code ==========

int main() {
    string inp;
    cin >> inp;
    int n = len(inp);
    string suf = inp;  // suffix min
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = min(suf[i], suf[i + 1]);
    }

    bool succ = false;
    for (int i = n - 2; i >= 0; i--) {
        if (inp[i] > suf[i + 1] and (i != 0 or suf[i + 1] != '0')) {
            succ = true;
            int max_index = -1;
            for (int j = i + 1; j < n; j++) {
                if (inp[j] < inp[i] and inp[j] > inp[max_index]) {
                    max_index = j;
                }
            }
            swap(inp[i], inp[max_index]);
            sort(inp.begin() + i + 1, inp.end());
            reverse(inp.begin() + i + 1, inp.end());
            break;
        }
    }
    
    cout << (succ ? inp : "0") << endl;
}
