#include<chrono>
#include<iostream>
#include<ctime>
#include <thread>

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "time1 cost: " << duration_cast<milliseconds>(high_resolution_clock::now() - t1).count() << std::endl;
}
