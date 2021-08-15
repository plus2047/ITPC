import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    G, = read_nums()
    # begin: x, num: n
    # (2 * x + n - 1) * n // 2 == G
    # 2 * x * n + n ** 2 - n == 2 * G
    # x = (2 * G + n - n ** 2) / (2 * n)
    res = 0
    n = 1
    while True:
        A = 2 * G + n - n ** 2
        B = 2 * n
        if A <= 0:
            break
        if A % B == 0:
            res += 1
        n += 1
    print("Case #%s: %s" % (_turn, res))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
