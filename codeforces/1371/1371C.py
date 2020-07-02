import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    a, b, n, m = read_num_list()
    if a + b < n + m:
        return False    
    if m <= min(a, b):
        return True
    return False


def main():
    T = read_num_list()[0]
    for i in range(T):
        res = solve(i + 1)
        print("yes" if res else "no")


if __name__ == "__main__":
    main()
