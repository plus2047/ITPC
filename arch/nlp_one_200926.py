import heapq

# %%
def main():
    inp = input()
    para = int(inp.split("/")[1])
    nodes = inp[:-2].split(";")
    igraph = {}
    degree = {}
    cost = {}
    free = []
    for s in nodes:
        name, deps, c = s.split(":")
        deps = deps[1:-1].split(",") if len(deps) > 2 else []
        for child in deps:
            if child not in igraph:
                igraph[child] = []
            igraph[child].append(name)
        degree[name] = len(deps)
        cost[name] = int(c)
        if degree[name] == 0:
            heapq.heappush(free, (0, name))
    
    worker = [0] * para
    finished_n = 0
    max_time = 0
    while len(free):
        start, node = heapq.heappop(free)
        w = heapq.heappop(worker)
        _w = max(w, start) + cost[node]
        max_time = max(max_time, _w)
        heapq.heappush(worker, _w)
        finished_n += 1
        for p in igraph.get(node, []):
            degree[p] -= 1
            if degree[p] == 0:
                heapq.heappush(free, (_w, p))

    res = max_time if finished_n == len(cost) else -1
    print(res)


if __name__ == "__main__":
    try:
        while True:
            main()
    except EOFError:
        pass


# %%
