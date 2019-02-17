#pragma once
#include <algorithm>

namespace contest {
template <typename num_t>
inline void dot(num_t* m1, num_t* m2, num_t* res, int d1, int d2, int d3) {
    std::fill(res, res + d1 * d3, 0);
    for (int i = 0; i < d1; i++) {
        int id3 = i * d3, id2 = i * d2;
        for (int k = 0; k < d2; k++) {
            int kd3 = k * d3;
            for (int j = 0; j < d3; j++) {
                res[id3 + j] += m1[id2 + k] * m2[kd3 + j];
            }
        }
    }
}

template <typename num_t>
inline void matrix_power(num_t* base, num_t* res, num_t* tmp, int dim, int n) {
    // res = base ^ n
    // this function need a tmp matrix.
    // because it's not a good idea to manage memory here.
    for (int i = 0; i < dim; i++) {
        int idim = i * dim;
        for (int j = 0; j < dim; j++) {
            res[idim + j] = i == j ? 1 : 0;
        }
    }
    int size = dim * dim;

    while (n) {
        if (n % 2 == 1) {
            // res = res * base
            dot(res, base, tmp, dim, dim, dim);
            std::copy(tmp, tmp + size, res);
        }
        // base = base * base
        dot(base, base, tmp, dim, dim, dim);
        std::copy(tmp, tmp + size, base);
        n /= 2;
    }
}
}  // namespace contest
// void test_linear(){
//     printf("test: dot\n");
//     int m1[6] = {1, 2, 3, 4, 5, 6};
//     int m2[6] = {1, 1, 1, 1, 1, 1};
//     int res[4];
//     dot(m1, m2, res, 2, 3, 2);
//     for(int i = 0; i < 4; i ++){
//         printf("%d ", res[i]);
//     }
//     printf("\n");

//     printf("test: Fibonacci Sequence\n");
//     for(int i = 0; i < 10; i ++){
//         int mf[4] = {0, 1, 1, 1};
//         int one[4] = {0, 1, 1, 1};
//         int res[4];
//         int tmp[4];
//         matrix_power(mf, res, tmp, 2, i);
//         std::copy(res, res + 4, mf);
//         printf("%d %d\n", mf[0] + mf[1], mf[2] + mf[3]);
//     }
// }