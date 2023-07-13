class FenwickTree:
    def __init__(self, size):
        self.tree = [0] * (size + 2)
        self.size = size + 1

    def add(self, idx, val):
        idx += 1
        while idx <= self.size:
            self.tree[idx] += val
            idx += (idx & -idx)

    def prefix_sum(self, idx):
        res = 0
        idx += 1
        while idx > 0:
            res += self.tree[idx]
            idx -= idx & -idx
        return res
