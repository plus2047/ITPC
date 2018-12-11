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
#include <cstdlib>

using namespace std;

// in this file, I try to imply a hash tab.
// it's quicker than unordered_set & I don't know why.

#define H_BITS 20 // Hash table size
#define TAB_SIZE (1U << H_BITS)

// this function is designed for unsigned int32
// but also work for unsigned int64 or int32 or int64
// return int64
#define hash32(x) (((x) >= 0 ? (x) : - (x)) * 2654435761 % TAB_SIZE)

int hash_tab_[TAB_SIZE];
bool used_[TAB_SIZE];
int size_ = 0;

bool insert(int x){
    if(size_ >= TAB_SIZE) { return false; }
    else { size_ ++; }

    auto index = hash32(x);
    while(used_[index]) {
        if(hash_tab_[index] == x){ return false; }
        else if(++ index >= TAB_SIZE) { index = 0; }
    }

    hash_tab_[index] = x;
    used_[index] = true;
    return true;
}

bool check(int x){
    auto index = hash32(x);
    while(used_[index]){
        if(hash_tab_[index] == x){ return true; }
        else if(++ index >= TAB_SIZE){ index = 0; }
    }
    return false;
}

bool remove(int x){
    auto index = hash32(x);
    while(used_[index]){
        if(hash_tab_[index] == x){
            used_[index] = false;
            size_ --;
            return true;
        }
        else if(++ index > TAB_SIZE){ index = 0; }
    }
    return false;
}

int main() {
    const int n_test = TAB_SIZE >> 1;
    unordered_set<int> stl_tab;
    vector<int> nums(n_test);
    for(int i = 0; i < n_test; i ++){
        nums[i] = rand();
    }

    auto t0 = clock();
    for(int i = 0; i < n_test; i ++) {
        insert(nums[i]);
    }
    auto t1 = clock();
    for(int i = 0; i < n_test; i ++){
        stl_tab.insert(nums[i]);
    }
    auto t2 = clock();

    printf("tab size_: %d, test count: %d.\n", TAB_SIZE, n_test);
    printf("simple hash tab: %d, std hash tab size_: %d.\n", size_, (int)stl_tab.size());
    printf("simple hash tab: %lf ms.\n", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
    printf("std hash tab: %lf ms.\n", 1000.0 * (t2 - t1) / CLOCKS_PER_SEC);
}
