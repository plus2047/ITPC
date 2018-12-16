// for programing contest
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "lib/show.h"

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;

int main() {
#ifdef __APPLE__
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int x[10];
    for(int i = 0; i < 10; i ++){
        x[i] = i;
    }
    show("x: ", x, x + 10);
    show("x: \n", x, x + 10, 5);
}
