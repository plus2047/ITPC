#pragma once
#include <algorithm>
#include <cassert>

namespace contest {

template <typename NUM = int>
struct Matrix {
    int dim1, dim2;
    vector<NUM> data;

    Matrix(int m, int n) : dim1(m), dim2(n), data(m * n) {}
    inline NUM& operator()(int m, int n) { return data[m * dim2 + n]; }

    void resize(int m, int n) { dim1 = m, dim2 = n, data.resize(m * n); }
    void as_eye() {
        as_zero();
        assert(dim1 == dim2);
        for (int i = 0; i < dim1; i++) (*this)(i, i) = 1;
    }
};

template <typename NUM>
void swap(Matrix<NUM>& a, Matrix<NUM>& b) {  // complexity: O(1)
    std::swap(a.dim1, b.dim1);
    std::swap(a.dim2, b.dim2);
    std::swap(a.data, b.data);
}

template <typename NUM = int>
struct MatrixCalculator {
    typedef Matrix<NUM> Mat;

    static void dot(Mat& A, Mat& B, Mat& result) {
        assert(A.dim2 == B.dim1);
        result.resize(A.dim1, B.dim2);
        for (int i = 0; i < A.dim1; i++) {
            for (int j = 0; j < B.dim2; j++) {
                NUM& res = result(i, j);
                res = 0;
                for (int k = 0; k < A.dim2; k++) {
                    res += A(i, k) * B(k, j);
                }
            }
        }
    }

    Mat _res = Mat(0, 0), _base = Mat(0, 0);
    void pow(const Mat& A, int n, Mat& result) {
        assert(A.dim1 == A.dim2);
        result.resize(A.dim1, A.dim2);
        result.as_eye();
        _res.resize(A.dim1, A.dim2);
        _res.as_eye();
        _base = A;

        while (n) {
            if (n % 2) {
                dot(result, _base, _res);
                swap(result, _res);
            }
            dot(_base, _base, _res);
            swap(_base, _res);
            n /= 2;
        }
    }
};
}  // namespace contest