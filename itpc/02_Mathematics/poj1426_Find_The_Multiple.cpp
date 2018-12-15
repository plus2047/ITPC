// poj1426_Find_The_Multiple.cpp

#include <cstdio>
using namespace std;

long long unsigned mul;
unsigned n;
bool dfs() {
    if (mul % n == 0) return true;
    if (mul * 10 > mul) {
        mul *= 10;
        if (dfs()) return true;
        mul += 1;
        if (dfs()) return true;
        mul /= 10;
    }
    return false;
}

int main() {
    while (scanf("%u", &n), n) {
        mul = 1;
        dfs();
        printf("%llu\n", mul);
    }
}
