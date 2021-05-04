import sys
import math


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


# python 3.7 in codejam donot has math.comb
def comb(n, k):
    return math.factorial(n) // math.factorial(k) // math.factorial(n - k)


def solve(_turn):
    def read_pair():
        ans, score = sys.stdin.readline().split()
        return ans, int(score)
    N, Q = read_nums()
    y, z, w = "", 0, 0

    # implement the last solution in the official analysis
    if N == 1:
        ans, score = read_pair()
        a1 = a2 = a3 = ans
        s1 = s2 = s3 = score
    elif N == 2:
        a1, s1 = read_pair()
        a2, s2 = read_pair()
        a3, s3 = a1, s1
    else:  # N == 3
        a1, s1 = read_pair()
        a2, s2 = read_pair()
        a3, s3 = read_pair()

    q1 = q2 = q3 = q4 = 0
    qtype = [0] * Q
    for i in range(Q):
        if a1[i] == a2[i] == a3[i]:
            q4 += 1
            qtype[i] = 4
        elif a2[i] == a3[i]:
            q1 += 1
            qtype[i] = 1
        elif a3[i] == a1[i]:
            q2 += 1
            qtype[i] = 2
        else:  # a1[i] == a2[i]
            q3 += 1
            qtype[i] = 3

    # t4 + t1 + (q2 - t2) + (q3 - t3) == s1
    # t4 + (q1 - t1) + t2 + (q3 - t3) == s2
    # t4 + (q1 - t1) + (q2 - t2) + t3 == s3

    # 3 t4 + 2 (q1 + q2 + q3) - (t1 + t2 + t3) = s1 + s2 + s3
    # t1 + t2 + t3 = 3 t4 + 2 (q1 + q2 + q3) - (s1 + s2 + s3)

    # t1 - t2 - t3 = s1 - t4 - q2 - q3
    # 2 t1 = 2 t4 + 2 q1 + q2 + q3 - s2 - s3
    # 2 t2 = 2 t4 + q1 + 2 q2 + q3 - s1 - s3
    # 2 t3 = 2 t4 + q1 + q2 + 2 q3 - s1 - s2

    best_num = 0
    total_num = 0
    n1 = n2 = n3 = n4 = 0
    for t4 in range(q4 + 1):
        _t1 = 2 * t4 + 2 * q1 + q2 + q3 - s2 - s3
        _t2 = 2 * t4 + q1 + 2 * q2 + q3 - s1 - s3
        _t3 = 2 * t4 + q1 + q2 + 2 * q3 - s1 - s2
        if _t1 < 0 or _t2 < 0 or _t3 < 0 or\
                _t1 > q1 * 2 or _t2 > q2 * 2 or _t3 > q3 * 2 or\
                _t1 % 2 or _t2 % 2 or _t3 % 2:
            continue
        t1, t2, t3 = _t1 // 2, _t2 // 2, _t3 // 2
        num = comb(q1, t1) * comb(q2, t2) * comb(q3, t3) * comb(q4, t4)

        total_num += num
        n1 += t1 * num // q1 if q1 else 0
        n2 += t2 * num // q2 if q2 else 0
        n3 += t3 * num // q3 if q3 else 0
        n4 += t4 * num // q4 if q4 else 0

    res = []

    # p_i = n_i / (q_i * total_num)

    def charnot(c):
        return 'T' if c != 'T' else 'F'

    for i in range(Q):
        if qtype[i] == 4:
            res.append(a1[i] if n4 * 2 > total_num else charnot(a1[i]))
        elif qtype[i] == 1:
            res.append(a1[i] if n1 * 2 > total_num else charnot(a1[i]))
        elif qtype[i] == 2:
            res.append(a2[i] if n2 * 2 > total_num else charnot(a2[i]))
        else:  # qtype[i] == 3
            res.append(a3[i] if n3 * 2 > total_num else charnot(a3[i]))

    z1 = max(n1, total_num - n1)
    z2 = max(n2, total_num - n2)
    z3 = max(n3, total_num - n3)
    z4 = max(n4, total_num - n4)

    z = z1 * q1 + z2 * q2 + z3 * q3 + z4 * q4
    w = total_num

    g = math.gcd(z, w)
    if g:
        z //= g
        w //= g

    y = "".join(res)

    print("Case #%s: %s %s/%s" % (_turn, y, z, w))


def main():
    T, = read_nums()
    for i in range(T):
        try:
            solve(i + 1)
        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()
