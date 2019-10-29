# graph[from_node] = [(to_node, weight)]

# %%


def dijkstra(graph, from_node):
    import heapq
    node_num = len(graph)
    res = [float("inf")] * node_num
    heap = []
    heapq.heappush(heap, (0, from_node))

    while len(heap):
        weight, node = heapq.heappop(heap)
        if weight >= res[node]:
            continue
        res[node] = weight
        for child in graph[node]:
            heapq.heappush(heap, (weight + child[1], child[0]))
    return res


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
    print(dijkstra(graph, 0))


if __name__ == "__main__":
    test()


# %%
