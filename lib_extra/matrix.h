#pragma once
#include <algorithm>
#include <cassert>

namespace contest {

typedef vector<vector<long long>> Mat;
const long long MOD = 1E9 + 7;

void dot(Mat& x, Mat& y, Mat& res) {
    int a = x.size(), b = y.size(), c = y[0].size();
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < c; j++) {
            res[i][j] = 0;
            for(int k = 0; k < b; k++) {
                res[i][j] = (res[i][j] + x[i][k] * y[k][j]) % MOD;
            }
        }
    }
}

void add(Mat& x, Mat& y, Mat& res) {
    int a = x.size(), b = x[0].size();
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            res[i][j] = (x[i][j] + y[i][j]) % MOD;
        }
    }
}

void pow(Mat& x, int n, Mat& res) {
    Mat base = x, _base = x, _res = res;
    int s = x.size();
    for(int i = 0; i < s; i++) {
        fill(res[i].begin(), res[i].end(), 0);
        res[i][i] = 1;
    }
    while(n) {
        if(n & 1) {
            dot(res, base, _res);
            swap(res, _res);
        }
        dot(base, base, _base);
        swap(base, _base);
        n >>= 1;
    }
}

}  // namespace contest