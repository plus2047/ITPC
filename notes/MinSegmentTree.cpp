// poj1785_Binary_Search_Heap_Construction.cpp
#include <vector>
#include <cstdio>
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

struct MinSegmentTree {
    vector<int> tree;
    size_t data_size;

    int _init(
            vector<int> &data,
            size_t node_index,
            size_t data_begin,
            size_t data_end
    ) {
        if (data_end - data_begin == 1) {
            tree[node_index] = data[data_begin];
        } else {
            size_t middle = data_begin + (data_end - data_begin) / 2;
            tree[node_index] = min(
                    _init(data, node_index * 2 + 1, data_begin, middle),
                    _init(data, node_index * 2 + 2, middle, data_end)
            );
        }
        return tree[node_index];
    }

    explicit MinSegmentTree(vector<int> &data) {
        data_size = data.size();
        assert((data_size & (data_size - 1)) == 0);
        tree.resize(data_size * 2 - 1);
        _init(data, 0, 0, data.size());
    }

    int _RMQ(
            size_t search_node,
            size_t search_begin,
            size_t search_end,
            size_t query_begin,
            size_t query_end
    ) {
        if(query_begin >= search_end || query_end <= search_begin) return INT_MAX;
        if(query_begin <= search_begin && query_end >= search_end) return tree[search_node];
        size_t middle = search_begin + (search_end - search_begin) / 2;
        return min(
                _RMQ(search_node * 2 + 1, search_begin, middle, query_begin, query_end),
                _RMQ(search_node * 2 + 2, middle, search_end, query_begin, query_end)
        );
    }


    int RMQ(size_t begin, size_t end) {
        return _RMQ(0, 0, data_size, begin, end);
    }


    void print() {
        for (size_t i = 0; i < tree.size(); i++) {
            cout << tree[i] << ',';
        }
        cout << endl;
    }
};

int main() {
    int _data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> data(_data, _data + 8);
    MinSegmentTree tree(data);
    tree.print();
    printf("%d\n", tree.RMQ(0, 2));
    printf("%d\n", tree.RMQ(1, 4));
    printf("%d\n", tree.RMQ(2, 3));
}
