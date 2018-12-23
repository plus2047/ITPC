// compare the speed of std::vector & std::array & c-array.
// result: if they are fix-size, the speed is almost the same.
// vector is even a little faster.

#include<vector>
#include<array>
#include<random>
#include<ctime>
using namespace std;

const int N = 10000;

int c_array[N][N];
vector<vector<int>> std_vector(N, vector<int>(N));
array<array<int, N>, N> std_array;

int main(){
    clock_t t0;
    int sum = 0;
    t0  = clock();
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            c_array[i][j] = 1;
            c_array[j][i] = 2;
        }
    }
    sum = 0;
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            sum += c_array[i][j];
        }
    }
    printf("sum: %d, c_array    read & write time: %lf\n", sum, 1.0 * (clock() - t0) / CLOCKS_PER_SEC);
    t0  = clock();
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            std_array[i][j] = 1;
            std_array[j][i] = 2;
        }
    }
    sum = 0;
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            sum += std_array[i][j];
        }
    }
    printf("sum: %d, std_array  read & write time: %lf\n", sum, 1.0 * (clock() - t0) / CLOCKS_PER_SEC);
    t0  = clock();
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            std_vector[i][j] = 1;
            std_vector[j][i] = 2;
        }
    }
    sum = 0;
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            sum += std_vector[i][j];
        }
    }
    printf("sum: %d, std_vector read & write time: %lf\n", sum, 1.0 * (clock() - t0) / CLOCKS_PER_SEC);
}