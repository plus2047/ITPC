import sys


def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]


def move(cmd: str, idx: int, mod=int(1E9)):
    x, y = 0, 0
    while idx < len(cmd):
        if cmd[idx].isalpha():
            if cmd[idx] == 'N':
                y += mod - 1
            elif cmd[idx] == 'S':
                y += 1
            elif cmd[idx] == 'E':
                x += 1
            elif cmd[idx] == 'W':
                x += mod - 1
            idx += 1
        elif cmd[idx].isdigit():
            end = idx
            while idx < len(cmd) and cmd[end].isdigit():
                end += 1
            n = int(cmd[idx:end]) % mod
            _x, _y, _idx = move(cmd, end + 1)
            x += _x * n
            y += _y * n
            idx = _idx
        else:
            assert cmd[idx] == ')'
            idx += 1
            break
        
        x %= mod
        y %= mod

    return x % mod, y % mod, idx

def solve(_turn):
    cmd = sys.stdin.readline().strip()
    dx, dy, end = move(cmd, 0)
    assert end == len(cmd)
    print("Case #%s: %s %s" % (_turn, dx + 1, dy + 1))


def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)


if __name__ == "__main__":
    main()
