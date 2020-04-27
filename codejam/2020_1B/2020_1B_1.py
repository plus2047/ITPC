import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    x, y = read_num_list()
    res = []
    if (x + y) % 2 == 0:
        res.append("IMPOSSIBLE")
    else:
        step = 0
        size = abs(x) + abs(y)
        while size > 0:
            size -= 2 ** step
            step += 1

        while x != 0 or y != 0:
            d = 2 ** (step - 1)
            step -= 1
            if abs(x) > abs(y):
                if x > 0:
                    x -= d
                    res.append("E")
                else:
                    x += d
                    res.append("W")
            else:
                if y > 0:
                    y -= d
                    res.append("N")
                else:
                    y += d
                    res.append("S")
        
        res.reverse()
    
    # if len(res[0]) == 1:
    #     step = 0
    #     _x, _y = 0, 0
    #     for act in res:
    #         d = 2 ** step
    #         step += 1
    #         if act == 'E':
    #             _x += d
    #         elif act == 'W':
    #             _x -= d
    #         elif act == 'N':
    #             _y += d
    #         else:
    #             _y -= d
    #     print(_x, _y)

    print("Case #%s: %s" % (_turn, "".join(res)))


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
