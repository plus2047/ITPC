#pragma once
#include <mutex>
#include <thread>
#include <vector>

namespace contest {
template <typename Input, typename Output>
std::vector<Output> thread_map(Output (*func)(Input), std::vector<Input>& inp,
                               std::size_t thread_num) {
    std::size_t idx = 0;
    std::vector<Output> res(inp.size());
    std::mutex inp_mu;

    std::vector<std::thread> threads;
    while (thread_num--) {
        threads.emplace_back([&]() {
            while (true) {
                inp_mu.lock();
                std::size_t _idx = idx++;
                inp_mu.unlock();

                if (_idx >= inp.size()) break;
                res[_idx] = func(inp[_idx]);
            }
        });
    }

    for (std::thread& t : threads) {
        if (t.joinable()) t.join();
    }

    return res;
}
}  // namespace contest