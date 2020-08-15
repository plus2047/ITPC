import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    N, M = read_nums()

    fact = vec(N + 1)
    fact[0] = fact[1] = 1
    for i in range(2, N + 1):
        fact[i] = fact[i - 1] * i % M

    c1 = vec(N + 1)
    c1[1] = 1
    for i in range(2, N + 1):
        c1[i] = fact[i]
        for j in range(1, i):
            c1[i] -= fact[i - j] * c1[j]
            c1[i] = (c1[i] % M + M) % M

    dp = vec(N + 1, 3)
    dp[1] = [1, 1, 1]
    for i in range(2, N + 1):
        dp[i] = [c1[i], c1[i], c1[i]]
        for j in range(1, i):
            c = c1[j]
            k = i - j
            dp[i][0] += c * dp[k][0] % M
            dp[i][1] += c * (dp[k][1] + dp[k][0]) % M
            dp[i][2] += c * (dp[k][2] + 2 * dp[k][1] + dp[k][0]) % M
        
    print("Case #%s: %s" % (_turn, dp[N][2] % M))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
