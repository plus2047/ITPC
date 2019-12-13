import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    minimum, maximum, mean, median = read_num_list()

    def echo(r):
        print("Case #%s: %s" % (_turn, r))

    if minimum > maximum or mean < minimum or mean > maximum or median < minimum or median > maximum:
        echo("IMPOSSIBLE")
        return
    elif minimum == maximum:
        echo(1)
        return
    elif mean == median and mean * 2 == maximum + minimum:
        echo(2)
        return
    elif mean * 3 == maximum + minimum + median:
        echo(3)
        return
    elif mean * 4 == maximum + minimum + median * 2:
        echo(4)
        return

    # minimum < maximum
    _min2 = minimum + median
    _max2 = median + maximum

    INF = 1 << 30
    res = INF
    LEN_MAX = 1 << 20

    # test even
    total = minimum + maximum + median * 2
    for N in range(LEN_MAX):
        # _mean = ((N * 2 + 4) * mean - total) / (N * 2)
        # if _min2 / 2 <= _mean <= _max2 / 2:
        #     res = min(res, N * 2 + 4)
        #     break
        _mean = (N * 2 + 4) * mean - total
        if _min2 * N <= _mean <= _max2 * N:
            res = min(res, N * 2 + 4)
            break
    
    # test odd
    total = minimum + maximum + median
    for N in range(LEN_MAX):
        _mean = (N * 2 + 3) * mean - total
        if _min2 * N <= _mean <= _max2 * N:
            res = min(res, N * 2 + 3)
            break

    echo(res if res != INF else "IMPOSSIBLE")


T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
