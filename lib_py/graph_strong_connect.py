# %%


def strong_connct(graph):
    def dfs_set_color(graph, color, begin_node, set_from, set_to):
        if color[begin_node] != set_from:
            return
        color[begin_node] = set_to
        for child in graph[begin_node]:
            dfs_set_color(graph, color, child, set_from, set_to)
    
    node_num = len(graph)
    color = [-1] * node_num

    for i in range(node_num):
        dfs_set_color(graph, color, i, -1, i + node_num)
    
    graph_inv = [list() for _ in range(node_num)]
    for from_node, to_node_list in enumerate(graph):
        for to_node in to_node_list:
            graph_inv[to_node].append(from_node)
    
    for i in range(node_num):
        if color[i] >= node_num:
            dfs_set_color(graph_inv, color, i, color[i], i)
    
    return color


# %%


def test():
    graph = [
        [2, 3],
        [0],
        [1],
        [4],
        []
    ]
    print(strong_connct(graph))


if __name__ == "__main__":
    test()


# %%


# %%
