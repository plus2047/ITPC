import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def succ(N, size, base):
    A = base ** size - 1
    B = N * (base - 1)
    return 0 if A == B else (1 if A > B else -1)


def solve(_turn):
    N = int(input())
    min_base = N - 1
    for size in range(61, 1, -1):
        left, right = 2, N - 1
        while left < right:
            mid = (left + right) // 2
            r = succ(N, size, mid)
            if r == 0:
                left = right = mid
            elif r == 1:
                right = mid - 1
            else:
                left = mid + 1
        if succ(N, size, left) == 0:
            min_base = left
            break

    print("Case #%s: %s" % (_turn, min_base))


T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
