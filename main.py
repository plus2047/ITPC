import sys
from math import factorial as fact

sys.stdin = open("_kickstart.in", "r")
sys.stdout = open("_main_py.out", 'w')

def main():
    T = int(input())
    for t in range(1, T + 1):
        count = 0
        print("Case #%s: %s" % (t, count))

if __name__ == "__main__":
    main()
