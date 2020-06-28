// for LeetCode
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename ITER>
void quick_sort(ITER begin, ITER end) {
    // quick sort for range [begin, end)
    if (end - begin <= 1) {
        return;
    }

    auto mid = *begin;
    auto left = begin, right = end;

    while (true) {
        while (--right > left && *right >= mid) {
        }
        if (left == right) {
            break;
        }
        *left = *right;
        while (++left < right && *left <= mid) {
        }
        if (left == right) {
            break;
        }
        *right = *left;
    }
    *left = mid;

    quick_sort(begin, left);
    quick_sort(++left, end);
}

template <typename ITER>
ITER kth_element(ITER begin, ITER end, int k) {
    if (end - begin <= 1) return begin;

    auto mid = *begin;
    auto left = begin, right = end;

    while (left < right) {
        while (true) {
            while (--right > left && *right >= mid) {
            }
            if (left == right) {
                break;
            }
            *left = *right;
            while (++left < right && *left <= mid) {
            }
            if (left == right) {
                break;
            }
            *right = *left;
        }
        *left = mid;

        int _k = left - begin;
        if (_k == k) {
            break;
        } else if (_k < k) {
            left = left + 1;
            right = end;
        } else {
            left = begin;
            right = left;
        }
    }

    return left;
}

template <typename ITER>
void quick_sort_slow_fast(ITER left, ITER right) {
    // quick sort for range [left, right]
    if (left >= right) {
        return;
    }

    auto mid = *right;
    auto slow = left - 1;

    for (auto fast = left; fast < right; fast++) {
        if (*fast <= mid) {
            swap(*++slow, *fast);
        }
    }
    swap(*++slow, *right);

    quick_sort_slow_fast(left, slow - 1);
    quick_sort_slow_fast(slow + 1, right);
}

int main() {
    int n_vec = 1024 * 1024;
    vector<int> vec1, vec2;
    for (int i = 0; i < n_vec; i++) {
        auto num = int(random());
        vec1.push_back(num);
        vec2.push_back(num);
    }
    auto t0 = clock();
    quick_sort_slow_fast(vec1.begin(), --vec1.end());
    auto t1 = clock();
    quick_sort(vec2.begin(), vec2.end());
    auto t2 = clock();

    for (int i = 0; i < n_vec; i++) {
        if (vec1[i] != vec2[i]) {
            printf("quick_sort err.\n");
            return 0;
        }
    }
    printf("successful.\n");
    printf("quick_sort_slow_fast speed: %lf ms\n",
           1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
    printf("quick_sort speed: %lf ms\n", 1000.0 * (t2 - t1) / CLOCKS_PER_SEC);
}
