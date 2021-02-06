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
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int px, py;
        cin >> px >> py;
        string s;
        cin >> s;
        int U = 0, D = 0, R = 0, L = 0;
        for (char c : s) {
            if (c == 'U') U++;
            if (c == 'D') D++;
            if (c == 'R') R++;
            if (c == 'L') L++;
        }
        int x = R - L, y = U - D;
        int dx = x - px, dy = y - py;
        // cout << dx << ' ' << dy << endl;
        if (((dx >= 0 and dx <= R) or (dx < 0 and -dx <= L)) and
            ((dy >= 0 and dy <= U) or (dy < 0 and -dy <= D))) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
