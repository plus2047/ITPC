import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]

def eprint(*args, **kw_args):
    print(*args, **kw_args)
    # print(*args, **kw_args, file=sys.stderr)


def solve(_turn, A, B):
    if A == B == 10 ** 9 - 5:
        for x in range(-5, 6):
            for y in range(-5, 6):
                print(x, y)
                ret = input()
                if ret == "CENTER":
                    return True
        return False
    elif A == B == 10 ** 9 - 50:
        left = up = 0
        while True:
            eprint(-10 ** 9 + left, 0)
            ret = input()
            if ret == "HIT":
                break
            left += 1
        while True:
            eprint(0, -10 ** 9 + up)
            ret = input()
            if ret == "HIT":
                break
            up += 1
        
        left, up = left - 50, up - 50
        for x in range(left - 4, left + 5):
            for y in range(up - 4, up + 5):
                eprint(x, y)
                ret = input()
                if ret == "CENTER":
                    return True
        return False
    else:
        print("Q")
        return False

def main():
    T, A, B = read_num_list()
    for i in range(T):
        if not solve(i + 1, A, B):
            break


if __name__ == "__main__":
    main()
