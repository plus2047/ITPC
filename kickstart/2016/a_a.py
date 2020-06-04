import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    N, = read_num_list()
    ss = [input().strip() for _ in range(N)]
    ss.sort(key=lambda s: (- len(set(s)) + (' ' in s), s))
    print("Case #%s: %s" % (_turn, ss[0]))


def main():
    T, = read_num_list()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
