def longest_common_subsequence(s1, s2):

    m, n = len(s1), len(s2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(m + 1):
        dp[i][0] = 0
    for j in range(n + 1):
        dp[0][j] = 0
    for i in range(m):
        for j in range(n):
            dp[i + 1][j + 1] = 1 + dp[i][j] if s1[i] == s2[j]\
                else max(dp[i][j + 1], dp[i + 1][j])

    com = []
    i, j = m, n
    while i > 0 and j > 0:
        if dp[i][j] == dp[i - 1][j]:
            i -= 1
        elif dp[i][j] == dp[i][j - 1]:
            j -= 1
        else:
            com.append(s1[i - 1])
            i -= 1
            j -= 1

    return com[::-1]


def test_longest_common_subsequence():
    s1 = [1, 2, 3, 5, 6, 7, 8, 9, 0]
    s2 = [1, 4, 5, 7, 0]
    print(longest_common_subsequence(s1, s2))


if __name__ == "__main__":
    test_longest_common_subsequence()
