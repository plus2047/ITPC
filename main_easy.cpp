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
template <typename num_t>

num_t greatest_common_divisor(num_t a, num_t b) {
    while (b) {
        tie(a, b) = make_pair(b, a % b);
    }
    return a;
}

int main() {
    cout << "HelloWorld!!!" << endl;
    cout << greatest_common_divisor(10, 5) << endl;
}
