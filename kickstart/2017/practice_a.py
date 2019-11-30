import sys


def solve(_turn):
    num = int(input())
    names = [input() + ' ' for _ in range(num)]
    names.sort()
    counts = [len(set(name)) for name in names]
    max_count = max(counts)
    res = [names[i] for i in range(num) if counts[i] == max_count][0]

    print("Case #%s: %s" % (_turn, res))


T = int(input())
for i in range(T):
    solve(i + 1)
