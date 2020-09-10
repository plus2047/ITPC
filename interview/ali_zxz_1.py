import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def main():
    N, = read_nums()
    res = N * (N - 1) + 1
    print(res)


if __name__ == "__main__":
    main()