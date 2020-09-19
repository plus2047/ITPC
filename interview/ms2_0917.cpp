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

struct ListNode {
    ListNode* next;
    int val;
};

bool hasCircle(ListNode* head) {
    if(not head or not head->next) return false;
    auto slow = head, fast = head->next;

    for(int i = 0; fast and slow; i++) {
        fast = fast->next;
        if(not fast) return false;
        if(fast == slow) return true;
        if(i % 2) slow = slow->next;
    }

    return false;
}

int countSeq(vector<vector<int>>& nums, int target) {
    int m = nums.size();
    if(m == 0) return 0;
    int n = nums[0].size();
    if(n == 0) return 0;

    vector<vector<pair<int, int>>> pos(target);
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) {
        if(nums[i][j] <= target) pos[nums[i][j] - 1].push_back({i, j});
    }

    vector<vector<int>> count(m, vector<int>(n));
    const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int val = 0; val < target; val++) {
        for(auto& p: pos[val]) {
            int i = p.first, j = p.second;
            if(val == 0) {
                count[i][j] = 1;
                continue;
            }
            for(int d = 0; d < 4; d++) {
                int x = i + D[d][0], y = j + D[d][1];
                if(x < 0 or y < 0 or x >= m or y >= n or nums[x][y] != val) continue;
                count[i][j] += count[x][y];
            }
        }
    }
    
    int result = 0;
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) {
        if(nums[i][j] == target) result += count[i][j];
    }
    return result;
}

int countSeqV2(vector<vector<int>>& nums, int target) {
    int m = nums.size();
    if(m == 0) return 0;
    int n = nums[0].size();
    if(n == 0) return 0;

    vector<vector<int>> count(m, vector<int>(n));
    queue<pair<int, int>> que;
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) {
        if(nums[i][j] == 1) {
            que.push({i, j});
        }
    }

    const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while(que.size()) {
        auto p = que.front();
        que.pop();
        int i = p.first, j = p.second;

        if(count[i][j] != 0) continue;
        if(nums[i][j] == 1) count[i][j] = 1;

        for(int d = 0; d < 4; d++) {
            int x = i + D[d][0], y = j + D[d][1];
            if(x < 0 or y < 0 or x >= m or y >= n) continue;

            if(nums[x][y] == nums[i][j] - 1) count[i][j] += count[x][y];
            if(nums[x][y] == nums[i][j] + 1) que.push({x, y});
        }
    }
    
    int result = 0;
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) {
        if(nums[i][j] == target) result += count[i][j];
    }
    return result;
}

int main() {
    vector<vector<int>> mat = {
        {1, 2, 3, 4}, 
        {2, 1, 2, 1},
        {1, 1, 1, 1}
    };
    cout << countSeq(mat, 3) << endl;
    cout << countSeqV2(mat, 3) << endl;
}
