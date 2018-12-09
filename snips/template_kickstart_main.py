import sys

sys.stdin = open("_in_debug.txt", "r")
sys.stdout = open("_out_py.txt", 'w')

for line in sys.stdin:
    print(line, end="", file=sys.stdout)
