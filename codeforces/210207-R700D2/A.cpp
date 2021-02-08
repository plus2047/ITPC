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

const int N = 1024;
char buff[N];
void solve() {
    scanf("%s", buff);
    for (int i = 0; buff[i]; i++) {
        if (i & 1) {
            buff[i] = buff[i] == 'z' ? 'y' : 'z';
        } else {
            buff[i] = buff[i] == 'a' ? 'b' : 'a';
        }
    }
    printf("%s\n", buff);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
