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

struct Graph {
    int N, M, edge_index = 0;
    vector<int> first, from, to, next;
    Graph(int N, int M) : N(N), M(M), first(N, -1), from(M), to(M), next(M) {}
    void add_edge(int _from, int _to) {
        from[edge_index] = _from;
        to[edge_index] = _to;
        next[edge_index] = first[_from];
        first[_from] = edge_index++;
    }
};

int main() { cout << "HelloWorld!!!" << endl; }
