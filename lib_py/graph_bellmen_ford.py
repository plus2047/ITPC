# graph[from_node] = [(to_node, weight)]

# %%


def bellmen_ford(graph, from_node):
    from collections import deque
    n_node = len(graph)

    deq = deque()
    deq.append(from_node)
    
    dist = [float("inf")] * n_node
    dist[from_node] = 0
    
    in_deq = [False] * n_node
    in_deq[from_node] = True
    
    cnt = [0] * n_node
    cnt[from_node] = 1

    while len(deq):
        node = deq.popleft()
        in_deq[node] = False

        for child, weight in graph[node]:
            d = dist[node] + weight
            if d >= dist[child]:
                continue
            dist[child] = d
            if not in_deq[child]:
                deq.append(child)
                cnt[child] += 1
                if cnt[child] > n_node:
                    return None

    return dist


# %%
def test():
    # sample from:
    # https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
    graph = [
        [(1, 4), (7, 8)],
        [(0, 4), (7, 11), (2, 8)],
        [(1, 8), (8, 2), (5, 4), (3, 7)],
        [(2, 7), (5, 14), (4, 9)],
        [(3, 9), (5, 10)],
        [(4, 10), (3, 14), (2, 4), (6, 2)],
        [(5, 2), (8, 6), (7, 1)],
        [(6, 1), (8, 7), (1, 11), (0, 8)],
        [(7, 7), (2, 2), (6, 6)]
    ]
    print(bellmen_ford(graph, 0))


if __name__ == "__main__":
    test()

# %%


# %%
