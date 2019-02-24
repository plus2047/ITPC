// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== persional contest env =====

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)

// ========== contest code ==========
void solve(int _turn) {
    int A, B, N;
    cin >> A >> B >> N;
    string res;
    while (true) {
        int mid = B - (B - A) / 2;
        cout << mid << endl;
        cin >> res;
        if (res == "CORRECT") {
            return;
        } else if (res == "TOO_SMALL") {
            A = mid;
        } else if (res == "TOO_BIG") {
            B = mid - 1;
        }
    }
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    // freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    // freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
