import random

N = 500000
M = 500000

print("%s %s" % (N, M))
nums = [str(random.randint(0, 10 ** 9)) for _ in range(N)]
print(" ".join(nums))
seen = set()
for _ in range(M):
    u, v = 0, 0
    while u == v or (u, v) in seen:
        u = random.randint(1, N)
        v = random.randint(1, N)
    w = random.randint(1, 10 ** 9)
    print("%s %s %s" % (u, v, w))
