import sys
from math import factorial as fact

sys.stdin = open("_kickstart.in", "r")
sys.stdout = open("_main_py.out", 'w')


def t_sort(x):
    d = {}
    for _t in x[1]:
        pair = _t.split(":")
        if(len(pair) == 2):
            try:
                key = int(pair[0])
            except:
                continue
            d[key] = pair[1]
    res = []
    for pair in sorted(d.items()):
        res.append("%s:%s" % (pair[0], pair[1]))
    return str(x[0]) + "\t" + " ".join(res)


def main():
    x = (1, ("2:1.0", "1:3.0"))
    print(t_sort(x))


if __name__ == "__main__":
    main()
