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

using namespace std;

const int D_MAX = 10;

inline int get(string& s, int pos) {
    return int(s[pos] - '0');
}

vector<int> get_cnt(string& s) {
    vector<int> cnt(D_MAX);
    for(char c: s) {
        for(int i = 0; i < int(c - '0'); i++) {
            cnt[i]++;
        }
    }
    return cnt;
}

int remain(string& base, string& inp, int delta, vector<int>& c1, vector<int>& c2) {
    int high = 0;
    for(int i = 0; i < inp.size(); i++) {
        high = max(high, get(base, i + delta) + get(inp, i));
    }
    int res = 0;
    for(int i = 0, j = high - 1; j >= 0 ;i++, j--) {
        int t = (i < D_MAX ? c1[i] : 0) + (j >= 0 ? c2[j] : 0);
        if(t != int(base.size()) and t != 0) {
            res++;
        }
    }
    return res;
}

int main() {
    string base, inp;
    cin >> base >> inp;
    vector<int> c1 = get_cnt(base);
    vector<int> c2 = get_cnt(inp);
    int res = INT_MAX;
    for(int p = 0; p + int(inp.size()) <= base.size(); p++) {
        res = min(res, remain(base, inp, p, c1, c2));
    }
    cout << res << endl;
}
