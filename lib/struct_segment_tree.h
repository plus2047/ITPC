#pragma once
#include <climits>
#include <map>
#include <string>

namespace contest {
struct UnnamedSegmentTree {
    typedef int NUM;
    typedef int IDX;

    struct Point {
        NUM change, depth;
    };
    std::map<NUM, Point> points;
    typedef std::map<IDX, Point>::iterator Iter;
    const NUM NUM_MIN = std::numeric_limits<NUM>::min();
    const NUM NUM_MAX = std::numeric_limits<NUM>::max();
    const IDX IDX_MIN = std::numeric_limits<IDX>::min();
    const IDX IDX_MAX = std::numeric_limits<IDX>::max();

    UnnamedSegmentTree() {
        points.insert(std::make_pair(NUM_MIN, Point({1, 0})));
        points.insert(std::make_pair(NUM_MAX, Point({-1, -1})));
    }

    void check(IDX begin, IDX end) {
        assert(begin < end and begin != IDX_MIN and end != IDX_MAX);
    }

    void insert(IDX begin, IDX end, NUM change) {
        check(begin, end);
        Iter it = points.lower_bound(begin);
        if (it->first == begin) {
            it->second.depth += change;
            it->second.change += change;
            if (it->second.change == 0) {
                it = points.erase(it);
            } else {
                it++;
            }
        } else {
            Point P = {change, prev(it)->second.depth + change};
            it = points.insert(it, std::make_pair(begin, P));
            it++;
        }
        // now 'it' point to next of begin.
        while (it->first < end) {
            it->second.depth += change;
            it++;
        }
        // now it point to the first point
        // which great or equal to end
        if (it->first == end) {
            it->second.change -= change;
            if (it->second.change == 0) {
                points.erase(it);
            }
        } else {
            Point P = {-change, prev(it)->second.depth - change};
            points.insert(it, std::make_pair(end, P));
        }
    }
    void erase(IDX begin, IDX end) {
        check(begin, end);
        Iter it = points.lower_bound(begin);
        if (it->first == begin) {
            Point& P = it->second;
            P.change = -(P.depth - P.change);
            P.depth = 0;
        } else {
            Point P = {-prev(it)->second.depth, 0};
            it = points.insert(it, std::make_pair(begin, P));
        }
        if (it->second.change == 0) {
            it = points.erase(it);
        } else {
            it++;
        }
        // now 'it' point to next of begin.
        while (it->first < end) {
            it = points.erase(it);
        }
        // now it point to the first point
        // which great or equal to end
        if (it->first == end) {
            if (it->second.depth == 0) {
                points.erase(it);
            } else {
                it->second.change = it->second.depth;
            }
        } else {
            NUM de = it->second.depth - it->second.change;
            if (de != 0) {
                points.insert(it, std::make_pair(end, Point({de, de})));
            }
        }
    }
    NUM min_depth(IDX begin, IDX end) {
        check(begin, end);
        Iter it = std::prev(points.upper_bound(begin));
        NUM res = NUM_MAX;
        while (it->first < end) {
            res = std::min(res, (it++)->second.depth);
        }
        return res;
    }
    NUM max_depth(IDX begin, IDX end) {
        check(begin, end);
        Iter it = std::prev(points.upper_bound(begin));
        NUM res = NUM_MIN;
        while (it->first < end) {
            res = std::max(res, (it++)->second.depth);
        }
        return res;
    }
    IDX total_length(IDX begin, IDX end) {
        check(begin, end);
        Iter it = std::prev(points.upper_bound(begin));
        IDX res = 0;
        while (it->first < end) {
            Iter nit = std::next(it);
            if (it->second.depth > 0) {
                res += std::min(nit->first, end) - begin;
            }
            begin = nit->first;
            it++;
        }
        return res;
    }
    NUM total_depth(IDX begin, IDX end) {
        check(begin, end);
        Iter it = std::prev(points.upper_bound(begin));
        NUM res = 0;
        while (it->first < end) {
            Iter nit = std::next(it);
            if (it->second.depth > 0) {
                res += (std::min(nit->first, end) - begin) * it->second.depth;
            }
            begin = nit->first;
            it++;
        }
        return res;
    }
    void print() {
        for (const std::pair<NUM, Point>& p : points) {
            printf("point: %d, change: %d, depth: %d\n", p.first,
                   p.second.change, p.second.depth);
        }
    }
};
}  // namespace contest