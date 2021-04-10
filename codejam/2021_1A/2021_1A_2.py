import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    M, = read_nums()
    cards = [read_nums() for _ in range(M)]
    total = sum(p[0] * p[1] for p in cards)
    res = 0
    for score in range(total, max(1, total - 64 * 499), -1):
        _sum = total
        _prod = score
        for p, n in cards:
            while _prod % p == 0 and n != 0:
                _prod //= p
                _sum -= p
                n -= 1
        if _sum == score and _prod == 1:
            res = score
            break

    print("Case #%s: %s" % (_turn, res))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
