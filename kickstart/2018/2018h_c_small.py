import sys
from math import factorial as fact

sys.stdin = open("_in_small.txt", "r")
sys.stdout = open("_out_py.txt", 'w')

def main():
    prime = 10 ** 9 + 7
    T = int(input())
    for t in range(1, T + 1):
        n, m = input().split()
        n, m = int(n), int(m)
        s = 0
        for k in range(m + 1):
            p = (-1) ** k * fact(2 * n - k) * 2 ** k
            mCk = fact(m) // fact(m - k) // fact(k)
            p *= mCk
            s += p
        s %= prime
        print("Case #%s: %s" % (t, s))

if __name__ == "__main__":
    main()
