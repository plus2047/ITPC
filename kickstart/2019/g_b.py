import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def solve(_turn):
    N, M = read_num_list()
    A = read_num_list()

    highest_bit = 64
    bit_sum = [0] * highest_bit
    bit_remain = [0] * highest_bit
    min_tail = [0] * highest_bit

    for i in range(highest_bit):
        mask = 1 << i
        for a in A:
            bit_sum[i] += mask & a
        bit_remain[i] = mask * N - bit_sum[i]
        min_tail[i] = (0 if i == 0 else min_tail[i - 1]) + min(bit_sum[i], bit_remain[i])
    
    k = 0
    for i in range(highest_bit - 1, -1, -1):
        if bit_remain[i] + (0 if i == 0 else min_tail[i - 1]) <= M:
            M -= bit_remain[i]
            k += 1 << i
        else:
            M -= bit_sum[i]
        if M < 0:
            k = -1
            break
    
    print("Case #%s: %s" % (_turn, k))

T = read_num_list()[0]
for i in range(T):
    solve(i + 1)
