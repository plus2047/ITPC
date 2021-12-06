#pragma once

#include <algorithm>
#include <stack>
#include <unordered_map>
#include <vector>

namespace contest {

// read python version for comment
std::vector<std::pair<int, int> > validArrangement(std::vector<std::pair<int, int> >& pairs) {
    std::unordered_map<int, std::vector<int> > G;
    std::unordered_map<int, int> degree;
    for (auto& p : pairs) {
        G[p.first].push_back(p.second);
        degree[p.first]++;
        degree[p.second]--;
    }
    int start = pairs[0].first;
    for (const auto& p : degree) {
        if (p.second == 1) {
            start = p.first;
            break;
        }
    }
    std::vector<int> path;
    std::stack<int> st;
    st.push(start);
    while (st.size()) {
        while (G[st.top()].size()) {
            int node = st.top();
            st.push(G[node].back());
            G[node].pop_back();
        }
        path.push_back({st.top()});
        st.pop();
    }
    std::vector<std::pair<int, int> > res;
    for (int i = int(path.size()) - 2; i >= 0; i--) {
        res.push_back({path[i + 1], path[i]});
    }
    return res;
}

}  // namespace contest