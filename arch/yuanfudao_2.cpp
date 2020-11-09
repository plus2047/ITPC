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

void dfs(vector<vector<int>>& G, vector<int>& W, vector<int64_t>& S, int n) {
    if(S[n] != INT_MIN) return;
    S[n] = W[n];
    for(int child: G[n]) {
        dfs(G, W, S, child);
        if(S[child] > 0) {
            S[n] += S[child];
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    vector<vector<int>> G(N);
    vector<int> W(N);
    for(int i = 0; i < N; i++) {
        int x, parent;
        scanf("%d%d", &x, &parent);
        if(parent != 0) {
            G[parent - 2].push_back(i);
        }
        W[i] = x;
    }
    vector<int64_t> S(N, INT_MIN);
    for(int i = 0; i < N; i++) {
        dfs(G, W, S, i);
    }
    printf("%lld\n", *max_element(S.begin(), S.end()));
}
