import sys


def dijkstra(graph, start, dist, back):
    import heapq
    node_num = len(graph)
    heap = []
    heapq.heappush(heap, (0, start, -1, ""))

    while len(heap):
        weight, node, parent, color = heapq.heappop(heap)
        if weight >= dist[node]:
            continue
        dist[node] = weight
        back[node] = (parent, color)
        for child in graph[node]:
            heapq.heappush(heap, (weight + child[1], child[0], node, child[2]))


def main():
    start, final = tuple(int(i) for i in sys.stdin.readline().split())
    N_MAX = 512
    graph = [[] for _ in range(N_MAX)]
    lines = sys.stdin.readlines()
    for line in lines:
        words = line.split("(")
        name = words[0].strip()
        for t in words[1:]:
            t = t.strip()[:-1].split()
            _f, _t, _w = [int(x) for x in t]
            graph[_f].append((_t, _w, name))
    dist = [float("inf")] * N_MAX
    back = [None] * N_MAX
    dijkstra(graph, start, dist, back)
    res = []
    total = dist[final]
    while final != start:
        res.append(back[final][1])
        final = back[final][0]
    print((" ".join(res[::-1]) + " " + str(total)) if total != float("inf") else "ERROR")

if __name__ == "__main__":
    main()

# %%
