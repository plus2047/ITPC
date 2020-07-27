import sys
def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]

x, y, n = read_num_list()
boss = set()
for i in range(n):
    boss.add(tuple(read_num_list()))

dp = [[0] * (y + 1) for _ in range(x + 1)]
dp[x][y] = 1

for i in range(x, -1, -1):
    for j in range(y, -1, -1):
        if (i, j) in boss:
            continue
        if i + 1 <= x:
            dp[i][j] += dp[i + 1][j]
        if j + 1 <= y:
            dp[i][j] += dp[i][j + 1]

print(dp[0][0])