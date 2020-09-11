import sys
import re
from collections import *


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    N, = read_nums()
    igraph = defaultdict(lambda: [])
    degree = defaultdict(lambda: 0)
    for i in range(N):
        line = input()
        words = [s for s in re.split("[=\(\)\,]+", line) if len(s) > 0]
        parent = words[0]
        childs = words[2:]
        degree[parent] += len(childs)
        for ch in childs:
            igraph[ch].append(parent)

    que = deque()
    for k, v in degree.items():
        if v == 0:
            que.append(k)
    
    count = 0
    while len(que):
        node = que.popleft()
        count += 1
        for p in igraph[node]:
            degree[p] -= 1
            if degree[p] == 0:
                que.append(p)

    print("Case #%s: %s" % (_turn, "GOOD" if count == N else "BAD"))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
