#pragma once
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace contest {

template <typename weight_t>
void dijstra(std::vector<std::vector<pair<int, weight_t> > >& G,
             std::vector<weight_t>& dist, vector<int>& trace, int start) {
    typedef std::tuple<weight_t, int, int> S;  // <dist, from, current>
    std::priority_queue<S, vector<S>, greater<S> > Q;
    Q.push({(weight_t)(0), -1, start});

    while (Q.size()) {
        weight_t d;
        int from, curr;
        tie(d, from, curr) = Q.top();
        Q.pop();

        if (dist[curr] <= d) continue;
        dist[curr] = d;
        trace[curr] = from;

        for (auto& p : G[curr]) {
            Q.push({p.second + d, curr, p.first});
        }
    }
}

template <typename weight_t>
bool bellman_ford(std::vector<std::vector<pair<int, weight_t> > >& G,
                  std::vector<weight_t>& dist, vector<int>& trace, int start) {
    int n = G.size();
    std::queue<std::tuple<weight_t, int, int> > Q;  // <dist, from, current>
    Q.push({(weight_t)(0), -1, start});
    vector<int> count(n);

    while (Q.size()) {
        weight_t d;
        int from, curr;
        tie(d, from, curr) = Q.front();
        Q.pop();

        if (dist[curr] <= d) continue;
        dist[curr] = d;
        trace[curr] = from;
        count[curr]++;
        if (count[curr] > n) return false;

        for (auto& p : G[curr]) {
            Q.push({p.first + d, curr, p.second});
        }
    }

    return true;
}

// donot set INF into INT_MAX, which cause overflow.
template <typename weight_t>
void flody(std::vector<std::vector<weight_t> >& D) {
    int n = int(D.size());
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}

// !!!UNCHECKED!!!
// template <int SIZE>
// void bit_flody(std::vector<std::bitset<SIZE> >& arrive) {
//     for (int k = 0; k < n; k++) {
//         for (int i = 0; i < n; i++) {
//             if (arrive[i][k]) {
//                 arrive[i] |= arrive[k];
//             }
//         }
//     }
// }

}  // namespace contest
