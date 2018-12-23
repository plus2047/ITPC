// get_prime_algorithm.
#include <vector>

// not recommand because it's slower.
std::vector<int> _get_prime_list_division(int less_than) {
    std::vector<int> prime(1, 2);
    for (int num = 3; num < less_than; num++) {
        bool is_prime = true;
        for (int i = 0; i < prime.size(); i++) {
            if (num % prime[i] == 0) {
                is_prime = false;
                break;
            } else if (prime[i] * prime[i] > num) {
                break;
            }
        }
        if (is_prime) prime.push_back(num);
    }
    return prime;
}

// recommand.
std::vector<int> get_prime_list_flag(int less_than) {
    std::vector<bool> flag((size_t)less_than, true);
    std::vector<int> prime;
    for (int num = 2; num < less_than; num++) {
        if (!flag[num])
            continue;
        else {
            prime.push_back(num);
            for (int i = 2; i * num < less_than; i++) flag[i * num] = false;
        }
    }
    return prime;
}

// #include <iostream>
// using namespace std;

// int speed_test(int lim) {
//     cout << "LIM: " << lim << endl;
//     auto t0 = clock();
//     auto prime_division = _get_prime_list_division(lim);
//     auto t1 = clock();
//     auto prime_flag = get_prime_list_flag(lim);
//     auto t2 = clock();
//     cout << "get prime (d) used time: " << (t1 - t0) / double(CLOCKS_PER_SEC)
//          << endl;
//     cout << "get prime (f) used time: " << (t2 - t1) / double(CLOCKS_PER_SEC)
//          << endl;
//     cout << "if two algorithm get the same result: "
//          << (prime_division == prime_flag) << endl;
// }

// int main() {
//     speed_test(10000);
//     speed_test(100000);
//     speed_test(1000000);
//     speed_test(10000000);
//     // flag algorithm O(1) is much speed than division algorithm.
//     // O(1) should be the fastest algorithm.
// }