// for LeetCode
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <random>
#include <ctime>

using namespace std;
const long _begin = 10000, _end = 1000000;

long _array[_end + 100];

int main(){
    long t0, t1;
    set<long> tree_set;
    unordered_set<long> hash_set;
    vector<long> vec((unsigned long)_end, 0);

    for(long count = _begin; count <= _end; count *= 10) {
        printf("\n");
        tree_set.clear();
        t0 = clock();
        for (int i = 0; i < count; i++) {
            tree_set.insert(random());
        }
        t1 = clock();
        printf("tree set insert: %d, using: %lfs.\n", (int) tree_set.size(), (t1 - t0) / double(CLOCKS_PER_SEC));

        hash_set.clear();
        t0 = clock();
        for (int i = 0; i < count; i++) {
            hash_set.insert(random());
        }
        t1 = clock();
        printf("hash set insert: %d, using: %lfs.\n", (int) hash_set.size(), (t1 - t0) / double(CLOCKS_PER_SEC));

        hash_set.clear();
        t0 = clock();
        for (int i = 0; i < count; i++) {
            hash_set.insert(random());
        }
        t1 = clock();
        printf("hash set insert: %d, using: %lfs. (inited)\n", (int) hash_set.size(), (t1 - t0) / double(CLOCKS_PER_SEC));

        t0 = clock();
        for (int i = 0; i < count; i++) {
            tree_set.count(random());
        }
        t1 = clock();
        printf("tree set count: %d, using: %lfs.\n", (int) tree_set.size(), (t1 - t0) / double(CLOCKS_PER_SEC));

        t0 = clock();
        for (int i = 0; i < count; i++) {
            hash_set.count(random());
        }
        t1 = clock();
        printf("hash set count: %d, using: %lfs.\n", (int) hash_set.size(), (t1 - t0) / double(CLOCKS_PER_SEC));

        t0 = clock();
        for (int i = 0; i < count; i++) {
            vec[i] = random();
        }
        t1 = clock();
        printf("vector using: %lfs.\n", (t1 - t0) / double(CLOCKS_PER_SEC));

        t0 = clock();
        for (int i = 0; i < count; i++) {
            _array[i] = random();
        }
        t1 = clock();
        printf("array  using: %lfs.\n", (t1 - t0) / double(CLOCKS_PER_SEC));
    }
}
