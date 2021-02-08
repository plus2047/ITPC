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
    int n;
    scanf("%d", &n);
    vector<int> arr(n + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    vector<int> a = {0}, b = {0};
    for (int i = 0; i < n; i++) {
        if (arr[i] == a.back() && arr[i] == b.back()) {
            continue;
        } else if (arr[i] == a.back()) {
            b.push_back(arr[i]);
        } else if (arr[i] == b.back()) {
            a.push_back(arr[i]);
        } else if (arr[i] == arr[i + 1]) {
            a.push_back(arr[i]);
        } else if (arr[i + 1] == a.back()) {
            a.push_back(arr[i]);
        } else {
            b.push_back(arr[i]);
        }
    }

    printf("%d\n", int(a.size() + b.size() - 2));
}
