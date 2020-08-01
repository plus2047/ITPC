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

int main() {
    int N;
    scanf("%d", &N);
    vector<pair<int, int>> ps;
    for(int i = 0; i < N; i++) {
        int begin, end;
        scanf("%d%d", &begin, &end);
        ps.push_back({begin, 1});
        ps.push_back({end, -1});
    }
    sort(ps.begin(), ps.end());
    int depth = 0, depth_max = 0;
    for(auto& p: ps) {
        depth += p.second;
        depth_max = max(depth_max, depth);
    }
    printf("%d\n", depth_max);
}
