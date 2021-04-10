import sys


def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())


def vec(*s):
    return [0] * s[0] if len(s) == 1 else [vec(*s[1:]) for _ in range(s[0])]


def solve(_turn):
    N, = read_nums()
    X = read_nums()
    res = 0
    last = str(X[0])
    # print(X)
    for i in range(1, len(X)):
        num = str(X[i])
        if len(num) == len(last):
            if num > last:
                last = num
            else:
                res += 1
                last = num + '0'
        elif len(num) > len(last):
            last = num
        else:  # len(num) < len(last)
            pre = last[:len(num)]
            delta = len(last) - len(num)
            if num > pre:
                res += delta
                last = num + '0' * delta
            elif num < pre:
                res +=  delta + 1
                last = num + '0' * (delta + 1)
            else: # num == pre
                suf = last[len(num):]
                if suf != '9' * len(suf):
                    res += delta
                    last = str(int(last) + 1)
                else:
                    res += delta + 1
                    last = num + '0' * (delta + 1)
        # print(last)

    print("Case #%s: %s" % (_turn, res))


def main():
    T, = read_nums()
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
