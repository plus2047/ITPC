#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

int main() {
    int N;
    scanf("%d", &N);
    vector<int> deg(N), edge_id(N);
    rep(i, N - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        deg[u]++, deg[v]++;
        edge_id[u] = edge_id[v] = i;
    }
    vector<int> label(N - 1, -1);
    int idx = 0;
    rep(i, N) {
        if (deg[i] == 1 and label[edge_id[i]] == -1) {
            label[edge_id[i]] = idx++;
        }
    }
    for (int val : label) {
        printf("%d\n", val != -1 ? val : idx++);
    }
}
