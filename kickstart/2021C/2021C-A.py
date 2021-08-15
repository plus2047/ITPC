import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    MOD = 10 ** 9 + 7
    N, K = read_nums()
    S = input()
    
    x, y = (N + 1) // 2, N // 2
    res = 1 if y != 0 and S[:y][::-1] < S[-y:] else 0
    for i in range(x):
        j = ord(S[i]) - ord('a')
        res = (res + j * pow(K, x - i - 1, MOD)) % MOD

    print("Case #%s: %s" % (_turn, res))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
