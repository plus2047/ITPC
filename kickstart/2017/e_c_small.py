import sys
import numpy as np
from numpy.linalg import norm


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def dist(a, b):
    return norm(a - b)


def solve(_turn):
    a, b, c = [np.array(read_num_list()) for _ in range(3)]

    x_list = [p[0] for p in (a, b, c)]

    print("Case #%s: %s" % (_turn, (max(x_list) - min(x_list)) / 6))

T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
