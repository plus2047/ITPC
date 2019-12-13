import sys
from collections import defaultdict
from functools import lru_cache


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    N, Q = read_num_list()
    A = [input() for _ in range(N + 1)]
    S = read_num_list()

    @lru_cache(None)
    def cal(q, t):
        if q == -1:
            return 0 if all(s == 0 for s in t) else - Q * Q

        tT = tuple(t[i] - (1 if A[i][q] == 'T' else 0) for i in range(N))
        tF = tuple(t[i] - (1 if A[i][q] == 'F' else 0) for i in range(N))
        dT = 1 if A[N][q] == 'T' else 0
        dF = 1 - dT

        return max(cal(q - 1, tT) + dT, cal(q - 1, tF) + dF)
    
    print("Case #%s: %s" % (_turn, cal(Q - 1, tuple(S))))

T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
