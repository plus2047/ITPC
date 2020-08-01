import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    print("Case #%s: %s" % (_turn, 0))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
