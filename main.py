import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    print("Case #%s: %s" % (_turn, 0))


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
