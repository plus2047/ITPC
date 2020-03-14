import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def is_pali(s):
    i, j = 0, len(s) - 1
    while i < j:
        if s[i] != s[j]:
            return False
        i, j = i + 1, j - 1
    return True


def is_pali_pre(s, size):
    i, j = (size - 1) // 2, size // 2
    while j < len(s) and i >= 0:
        if s[i] != s[j]:
            return False
        i, j = i - 1, j + 1
    return True


def solve(_turn):
    L, N, K = read_num_list()

    def pre_count(s):
        total = 0
        for pali_size in range(len(s), N + 1):
            if is_pali_pre(s, pali_size):
                total += pow(L, max(0, (pali_size + 1) // 2 - len(s)))
        return total

    # treat "" as a valid pali.
    # but all pali is zero-indexed
    pre = ""
    target = K

    c_begin, c_end = ord('a'), ord('a') + L
    while target != 0 or not is_pali(pre):
        # print("target: %s, pre: %s" % (target, pre))
        if is_pali(pre):
            target -= 1

        curr_idx = 0
        succ = False
        for c in range(c_begin, c_end):
            _pre = pre + chr(c)
            cnt = pre_count(_pre)
            if target < curr_idx + cnt:
                pre = _pre
                target -= curr_idx
                succ = True
                break
            else:
                curr_idx += cnt

        if not succ:
            pre = ""
            break
        

    print("Case #%s: %s" % (_turn, len(pre)))


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
