import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    R, C = read_nums()

    res = 0
    if R == 1 or C == 1:
        x = R if C == 1 else C
        res = 2 * (x // 3) + x % 3
    elif R == 2 or C == 2:
        x = R if C == 2 else C
        res = 2 * (x // 3) + x % 3
        res *= 2
    else:  # R >= 3 and C >= 3
        res += (C // 3) * 2 * R
        if C % 3 >= 1:
            res += 2 * (R // 3) + R % 3
        if C % 3 >= 2:
            res += 2 * (R // 3) + (1 if R % 3 else 0)
    
    print("Case #%s: %s" % (_turn, res))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
