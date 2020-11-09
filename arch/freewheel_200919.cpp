#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
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
#include <list>

using namespace std;

int minCost(int n, vector<int>& cuePoints) {
    int m = cuePoints.size();
    auto ps = cuePoints;
    ps.push_back(0);
    ps.push_back(n);
    sort(ps.begin(), ps.end());
    
    // dp[i][j] == the min cost to insert points [i, j]
    vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
    for(int s = 1; s <= m; s++) {
        for(int i = 1, j = s; j <= m; i++, j++) {
            int cost = INT_MAX;
            for(int k = i; k <= j; k++) {
                cost = min(cost, dp[i][k - 1] + dp[k + 1][j]);
            }
            dp[i][j] = cost + ps[j + 1] - ps[i - 1];
        }
    }
    
    return dp[1][m];
}

int main() {
    vector<int> nums;
    nums = {1, 3, 4, 5};
    cout << minCost(7, nums) << endl;
}
