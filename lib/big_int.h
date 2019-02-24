#pragma once

#include <algorithm>
#include <vector>

namespace contest {
typedef int NUM;
// number: 1234 is save as [4, 3, 2, 1]
typedef std::vector<NUM> BigInt;

void carry(BigInt& num) {
    int last = int(num.size()) - 1;
    for (int i = 0; i < last; i++) {
        if (num[i] > 9) {
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        } else if (num[i] < 0) {
            NUM sub = (num[i] + 1) / 10 - 1;
            num[i + 1] += sub;
            num[i] -= sub * 10;
        }
    }
    while (num.back() > 9) {
        NUM next_num = num.back() / 10;
        num.back() %= 10;
        num.push_back(next_num);
    }
    while (num.back() == 0) num.pop_back();
    assert(num.back() > 0);
}

void add(const BigInt& a, const BigInt& b, BigInt& result) {
    int alen = int(a.size()), blen = int(b.size());
    result.resize(std::max(alen, blen));
    std::fill(result.begin(), result.end(), 0);
    for (int i = 0; i < alen; i++) result[i] += a[i];
    for (int i = 0; i < blen; i++) result[i] += b[i];
    carry(result);
}

void multiply(const BigInt& a, const BigInt& b, BigInt& result) {
    int alen = int(a.size()), blen = int(b.size());
    result.resize(alen + blen);
    std::fill(result.begin(), result.end(), 0);
    for (int i = 0; i < alen; i++) {
        for (int j = 0; j < blen; j++) {
            result[i + j] += a[i] * b[j];
        }
    }
    carry(result);
}

bool less(const BigInt& a, const BigInt& b) {
    int alen = int(a.size()), blen = int(b.size());
    if (alen != blen) return alen < blen;
    for (int i = alen - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

void subtract(const BigInt& a, const BigInt& b, BigInt& result) {
    // assert(!less(a, b))
    int alen = int(a.size()), blen = int(b.size());
    result.resize(alen);
    std::fill(result.begin(), result.end(), 0);
    for (int i = 0; i < alen; i++) {
        result[i] += a[i];
        if (i < blen) result[i] -= b[i];
    }
    carry(result);
    assert(result.back() >= 0);
}
}  // namespace contest