import sys

sys.stdin = open("_kickstart.in", "r")
sys.stdout = open("_main_py.out", 'w')


def sol(nums):
    p1, p2 = 0, len(nums) - 1
    while True:
        while nums[p1] % 2 == 0:
            nums[p1], nums[p2] = nums[p2], nums[p1]
            p2 -= 1
        p1 += 1
        if p1 == p2:
            break

    return nums


if __name__ == "__main__":
    print(sol([7, 1, 2, 3, 4, 5]))
