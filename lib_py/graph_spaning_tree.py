# graph: [[(to, weight)]]
# %%


def min_spanning_tree(edges):
    node_num = len(edges)
    mf = list(range(node_num))

    def find(x): return x if mf[x] == x else find(mf[x])

    def merge(x, y): mf[find(y)] = find(x)
    edges.sort(key=lambda e: e[2])
    span = []
    for e in edges:
        x, y, weight = e
        if find(x) != find(y):
            merge(x, y)
            span.append(e)
    return span

# %%


def test():
    edges = [
        (0, 3, 3),
        (0, 1, 1),
        (1, 3, 5),
        (1, 2, 6),
        (1, 4, 1),
        (2, 4, 5),
        (2, 5, 2),
        (3, 4, 1),
        (4, 5, 4)
    ]

    print(min_spanning_tree(edges))


if __name__ == "__main__":
    test()

# %%
