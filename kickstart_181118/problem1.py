import sys

sys.stdin = open("_in_small.txt", 'r')
sys.stdout = open("_out_py.txt", 'w')


def small_solve(case):
    nums = list(map(int, case.split(" ")))
    count = 0
    for x in range(len(nums)):
        for y in range(x + 1, len(nums)):
            for z in range(y + 1, len(nums)):
                xn, yn, zn = nums[x], nums[y], nums[z]
                if xn == yn * zn or yn == xn * zn or zn == xn * yn:
                    count += 1
    return count


if __name__ == "__main__":
    T = int(input())
    for t in range(1, T+1):
        n = int(input())
        print("Case #%s: %s" % (t, small_solve(input())))
