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

int kth(vector<int>& a, int left, int right, int k) {
    int mid = a[left];
    int p1 = left, p2 = right;
    while(p1 < p2) {
        while(a[p1] <= mid and p1 < p2) p1++;
        while(a[p2] >= mid and p1 < p2) p2--;
        swap(a[p1], a[p2]);
    }
    int mid_i = p1 - left;
    if(mid_i == k) return a[mid_i];
    else if(mid_i < k) return kth(a, mid_i + 1, right, k - mid_i - 1);
    else return kth(a, left, mid_i - 1, k);
}

int findKth(vector<int> a, int n, int K) {
    // write code here
    return kth(a, 0, n - 1, K - 1);
}

int main() {
    vector<int> nums = {1, 3, 5, 2, 2};
    cout << findKth(nums, 5, 3) << endl;
}
