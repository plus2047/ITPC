import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def upper_bound(fn, left, right):
    if fn(right):
        return right
    while right - left > 1:
        mid = (left + right) // 2
        if fn(mid):
            left = mid
        else:
            right = mid
    return left

def solve(_turn):
    L, R = read_num_list()
    
    b1 = 1
    d1 = abs(L - R)

    b2 = upper_bound(lambda e: (b1 + e - 1) * (e - 1) <= d1 * 2, b1, d1 + 1)
    x1 = (b1 + b2 - 1) * (b2 - 1) // 2

    if L > R:
        L -= x1
    else:
        R -= x1
        
    d2, d3 = (L, R) if L >= R else (R, L)
    b3 = b2 + 1

    def sum_d2(first, cnt):
        return (first * 2 + (cnt - 1) * 2) // 2 * cnt
    
    c2 = upper_bound(lambda c: sum_d2(b2, c) <= d2, 0, d2)
    c3 = upper_bound(lambda c: sum_d2(b3, c) <= d3, 0, d3)

    n = b2 - 1
    if c2 > 0:
        n = max(n, b2 + (c2 - 1) * 2)
    if c3 > 0:
        n = max(n, b3 + (c3 - 1) * 2)

    x2, x3 = sum_d2(b2, c2), sum_d2(b3, c3)

    # print("L, R, b2:", L, R, b2)
    # print("c2, c3, x2, x3:", c2, c3, x2, x3)

    if L >= R:
        L -= x2
        R -= x3
    else:
        L -= x3
        R -= x2

    print("Case #%s: %s %s %s" % (_turn, n, L, R))


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
