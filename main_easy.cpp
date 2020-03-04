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

#include "lib/geometry.h"

using namespace std;

const double PI = 3.1415926535897932354626;

int main() {
    contest::Vec2D<double> vec = {1., 1.};
    cout << contest::angle(vec) / PI * 180. << endl;
    cout << "HelloWorld!!!" << endl;
}
