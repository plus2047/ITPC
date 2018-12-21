#ifndef __NAMED_TUPLE_H__
#define __NAMED_TUPLE_H__

#include<tuple>

template <typename TUPLE, size_t FIELD>
bool upper(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) > std::get<FIELD>(b);
}
template <typename TUPLE, size_t FIELD>
bool lower(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) < std::get<FIELD>(b);
}

// test & sample:

// #include<algorithm>
// using namepsace std;

// void test_named_tuple() {
//     typedef tuple<int, int> People;
//     const size_t id = 0, age = 1;

//     vector<People> peoples;
//     const int SIZE = 5;
//     for (int i = 0; i < SIZE; i++) {
//         peoples.push_back({SIZE - i, i});
//     }

//     sort(peoples.begin(), peoples.end(), upper<People, age>);
//     for_each(peoples.begin(), peoples.end(),
//              [](auto& p) { printf("age: %d\n", get<age>(p)); });
//     sort(peoples.begin(), peoples.end(), lower<People, id>);
//     for_each(peoples.begin(), peoples.end(),
//              [](auto& p) { printf("id: %d\n", get<id>(p)); });
// }
#endif  // define __NAMED_TUPLE_H__