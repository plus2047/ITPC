import sys
import math

if sys.platform == "darwin":
    sys.stdin = open("_kickstart.in", "r")
    sys.stdout = open("_main_py.out", 'w')

def sol(_turn):
    _, L = [int(v) for v in input().split()]
    vals = [int(x) for x in input().split()]

    for diff in range(L):
        if vals[diff] != vals[diff + 1]:
            break
    
    cd = math.gcd(vals[diff], vals[diff + 1])
    
    primes = [0] * (L + 1)
    primes[diff] = vals[diff] // cd
    for i in range(diff - 1, -1, -1):
        primes[i] = vals[i] // primes[i + 1]
    for i in range(diff + 1, L + 1):
        primes[i] = vals[i - 1] // primes[i - 1]
    
    plist = sorted(list(set(primes)))
    pdict = {v: chr(ord('A') + i) for i, v in enumerate(plist)}
    res = [pdict[v] for v in primes]
    print("Case #%d: " % _turn + "".join(res))

if __name__ == "__main__":
    t = int(input())
    for i in range(t):
        sol(i + 1)
