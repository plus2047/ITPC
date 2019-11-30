import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    mod = 10 ** 9 + 7;
    R, C = read_num_list()
    if R > C:
        R, C = C, R

    res = (2 * C * R**3 - R**4 - 2 * C * R + R**2) // 12 % mod

    print("Case #%s: %s" % (_turn, res))

T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
