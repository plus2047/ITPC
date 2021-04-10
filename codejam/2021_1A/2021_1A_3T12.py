import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    def read_pair():
        ans, score = sys.stdin.readline().split()
        return ans, int(score)
    N, Q = read_nums()
    y, z, w = "", 0, 0
    if N == 1:
        ans, score = read_pair()
        if score >= Q - score:
            y, z, w = ans, score, 1
        else:
            y = "".join('F' if c == 'T' else 'T' for c in ans)
            z, w = Q - score, 1
    elif N == 2:
        a1, s1 = read_pair()
        a2, s2 = read_pair()
        diff = sum(c1 != c2 for c1, c2 in zip(a1, a2))
        t = (diff + s1 + s2)
        assert t % 2 == 0
        t //= 2
        a, b, c = t - diff, t - s2, t - s1
        keep_same = a >= Q - diff - a
        y = []
        for c1, c2 in zip(a1, a2):
            if c1 == c2:
                y.append(c1 if keep_same else ('T' if c1 == 'F' else 'F'))
            else:
                y.append(c1 if b >= c else c2)
        y = "".join(y)
        z = max(a, Q - diff - a) + max(b, c)
        w = 1
    else:  # N == 3, quit
        pass

    print("Case #%s: %s %s/%s" % (_turn, y, z, w))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
