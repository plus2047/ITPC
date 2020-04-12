#%%
import sys
from functools import lru_cache


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


@lru_cache(None)
def tri_val(r, k):
    if k == 1 or k == r:
        return 1
    return tri_val(r - 1, k) + tri_val(r - 1, k - 1)


def to_right_edge(r, k):
    res = 0
    while True:
        n = tri_val(r, k)
        res += n
        r -= 1
        if r < k:
            break
    return res


def check_sum(res):
    return sum(tri_val(*p) for p in res)

#%%
def solve(_turn):

    def show_res(res):
        print("Case #%s:" % (_turn,))
        for r, k in res:
            print("%s %s" % (r, k))

    n = read_num_list()[0]
    if n <= 500:
        show_res([(i + 1, 1) for i in range(n)])
        return

    lim = 6
    n -= lim
    res = [(i + 1, 1) for i in range(lim)]
    r, k = lim + 1, 2
    while n:
        n -= tri_val(r, k)
        res.append((r, k))
        if to_right_edge(r + 1, k + 1) <= n:
            r += 1
            k += 1
        else:
            r -= 1
    
    # print("size: ", len(res))
    # print("real sum: ", check_sum(res))
    show_res(res)


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()


# %%
