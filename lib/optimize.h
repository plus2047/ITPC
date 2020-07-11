#pragma once

namespace contest {

// triple search the MIN point of func.
// the func must has only one min point in [left, right]
// and it must be strictly monotonicity in each side of this min point.
template <typename FUNC>
double triple_search(FUNC loss_func, double left, double right) {
    const double DELTA = 1E-9;
    while (right - left > DELTA) {
        double t = (right - left) / 3;
        double m1 = left + t, m2 = right - t;
        double loss1 = loss_func(m1), loss2 = loss_func(m2);
        if (loss1 > loss2) {
            left = m1;
        } else {
            right = m2;
        }
    }
    return (left + right) / 2;
}

// search the min point of func.
template <typename FUNC>
double anneal(FUNC loss_func, double left, double right) {
    // set those values carefully. when it's possible, set them big enough.
    const int EPOCH_NUM = 8, RAND_SEARCH_NUM = 16;
    // and set this small enough.
    const double MIN_STEP = 1E-8, STEP_REDUCE = 0.8;

    double global_x = left;
    double global_min_loss = loss_func(left);

    for (int i = 0; i < EPOCH_NUM; i++) {
        double step = right - left;
        double x = left + step * rand() / RAND_MAX;
        double loss = loss_func(x);
        while (step > MIN_STEP) {
            double x1 = x, loss1 = loss_func(x);
            for (int j = 0; j < RAND_SEARCH_NUM; j++) {
                double x2 = x + (2.0 * rand() / RAND_MAX - 1.0) * step;
                double loss2 = loss_func(x2);
                if (loss2 < loss1) {
                    x1 = x2, loss1 = loss2;
                }
            }
            x = x1, loss = loss1;
            step *= STEP_REDUCE;
        }
        if (loss < global_min_loss) {
            global_x = x, global_min_loss = loss;
        }
    }

    return global_x;
}

}  // namespace contest
