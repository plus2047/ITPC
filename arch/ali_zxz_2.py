import sys

def read_nums():
    return tuple(int(i) for i in sys.stdin.readline().split())

def main():
    _n = read_nums()
    if len(_n) != 1: return False
    N, = _n

    words = []
    for i in range(N): words.append(input())
    
    sec = sys.stdin.readline().strip()[:-1].split()
    _sec = " ".join(sec)
    
    tab = {" " : " "}
    res = []
    def dfs(i, j):
        if len(sec[i]) != len(words[j]) and len(res) < 2: return False

        added = []
        for k in range(len(sec[i])):
            f, t = sec[i][k], words[j][k]
            if (f in tab and tab[f] != t) or (t in tab and tab[t] != f):
                return False
            if f not in tab:
                tab[f] = t
                tab[t] = f
                added.append(f)
                if f != t:
                    added.append(t)
        
        if i + 1 == len(sec):
            res.append("".join(tab[c] for c in _sec))
        else:
            [dfs(i + 1, _j) for _j in range(len(words))]

        for c in added: del tab[c]

    for j in range(len(words)): dfs(0, j)
    
    print("-." if len(res) != 1 else res[0] + '.')
    return True

if __name__ == "__main__":
    while main(): pass
