import sys

sys.stdin = open("_debug.in", "r")
sys.stdout = open("_main_py.out", 'w')

def cnt(right, prefix):
    pre_len, right_len = len(prefix), len(right)
    _cnt = 1
    for idx in range(pre_len + 1, right_len):
        _cnt += 10 ** (idx - pre_len)
    if pre_len != right_len:
        right_pre = right[:pre_len]
        if prefix == right_pre:
            _cnt += int(right[pre_len:]) + 1
        elif prefix < right_pre:
            _cnt += 10 ** (right_len - pre_len)
    return _cnt

def sol(right, target):
    right, target, res = str(right), target + 1, ""
    while target > 0:
        if target == 1:
            return res
        target -= 1
        for n in range(0 if res != "" else 1, 10):
            _cnt = cnt(right, res + str(n))
            if _cnt >= target:
                res += str(n)
                break
            target -= _cnt
    return res

if __name__ == "__main__":
    print(sol(250, 126))
