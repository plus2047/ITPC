"""
趣味题目：

一个打字机可以执行「全选、复制、粘贴、删除一个字符」四种操作。
初始状态时，屏幕上只有一个 a
求问若想得到 n 个 a 需要多少次操作？

总体思路：
首先，全选-复制-粘贴 N 次可以绑定到一起分析，因为虽然粘贴过程中可以删除，但这跟粘贴结束后再删除是等价的。
于是简化到只需要考虑两类操作：删除，或者全选-复制-粘贴 N 次。

在 DP 空间中，一个数字可以视为一个状态节点，操作可以视为状态节点之间的边，DP 空间视为一个图。
按上述，边只有两类，操作次数就是边长。于是问题转换成寻找 DP 空间中节点 1 和节点 n 之间的最短路径。

最短路径 Dijkstra 算法需要枚举从某个节点出发的所有边，所以需要论证，连续的粘贴不会超过 N 次。
我们可以论证一个更宽泛的界限，int32 范围内的任意数字需要的操作次数不会超过 160 次。
证明非常简单，考虑一个目标数字 n 最多五次就能将该数字减半：
如果是偶数，直接消耗四次操作将其减半。如果是奇数，则加一再减半。

所以 Dijkstra 算法从任意节点出发最多考虑 160 条边即可。
另外需要注意一点，目标节点 n 的上一个节点不一定小于 n 所以 Dijkstra 构造图时不能只构造 [0, n]
而是要构造 [0, n+160]
Dijkstra 具有 O(n log n) 的复杂度，最多能处理大约 10^6 的输入数据。

-----

按上述论述，操作次数的上界是 n 的对数函数。为此，能否构造具有对数时间复杂度的解法？

对数时间复杂度的解法当然不能构造图，不能从 1 开始向目标数字搜索，可以考虑从目标数字开始反向搜索 1.
但是，「最后一步」是删除还是复制粘贴是难以判断的，因此仍然需要从 n 开始 BFS. 
相对于 Dijkstra, 这样搜索能够跳过大量节点。

但 BFS 效率与边数量密切相关，如果使用 160 的上界是难以运行的。有一种直觉是连续粘贴或者删除次数不会太多。
使用以下代码实验发现，限制连续粘贴或者删除不超过 12 次就能在 10^4 范围内保证正确，但这个下界难以证明。
主要难点发生在难以论证复制粘贴质数次的情况可以被较少的复制粘贴次数代换。

-----

补充一点可能有用的论证，
最优操作序列一定可以被等价转换为「全选复制粘贴 N1 次-删除 M1 次-全选复制粘贴 N2 次 ...」
如此交替进行，并且删除次数可以为 0. 可以证明删除次数一定不多于上次粘贴次数，否则只需要将一个删除操作
替换到上次复制粘贴之前即可。
"""

import heapq



def dijkstra(n, PASTE_LIM=160, backtracking=False):
    m = n + PASTE_LIM
    ops = [n + 4] * m
    back = [-1] * m
    ops[0], ops[1] = 1, 0
    back[0] = 1
    q = [(0, 1)]
    while q:
        step, x = heapq.heappop(q)
        if ops[x] < step:
            continue

        y, next = x - 1, step + 1
        if y > 0 and ops[y] > next:
            ops[y] = next
            back[y] = x
            heapq.heappush(q, (next, y))

        for p in range(2, PASTE_LIM):
            y, next = x * p, step + p + 2
            if y < m and ops[y] > next:
                ops[y] = next
                back[y] = x
                heapq.heappush(q, (next, y))

    return (ops, back) if backtracking else ops


def beam(n, PASTE_LIM=12, DFS_MARGIN=1024, margin=[], cache={}):
    if len(margin) != DFS_MARGIN:
        margin.clear()
        margin.extend(dijkstra(DFS_MARGIN, backtracking=False)[:DFS_MARGIN])

    sortest = n + 3
    def dfs(n, curr=0):
        if n < DFS_MARGIN:
            return margin[n]
        if n in cache:
            return cache[n]
        if curr > sortest:
            return sortest
        
        min_ops = sortest
        for i in range(PASTE_LIM):
            x = n + i
            for j in range(2, PASTE_LIM):
                if x % j == 0:
                    y = x // j
                    min_ops = min(min_ops, dfs(y, curr + i + j + 2) + i + j + 2)
        
        cache[n] = min_ops
        return min_ops

    return dfs(n)


if __name__ == "__main__":
    ops, back = dijkstra(10**4, backtracking=True)

    print("\n### basic test cache for dijkstra ###")
    for x in (11, 12, 18, 33, 41, 193, 256, 257, 999, 1000, 6543, 10000):
        y = x
        track = []
        while back[y] != -1:
            track.append(back[y])
            y = back[y]            
        print(x, ops[x], track)

    print("\n### check beam == dijkstra ###")
    for i in range(10 ** 4):
        x, y = ops[i], beam(i)
        assert(ops[i] == beam(i)), "n: %s, dijkstra: %s, beam: %s" % (i, x, y)
    print("check ok")

    print("\n### test huge number for beam ###")
    for x in range(32):
        y = 2 ** x + 7
        print("y = 2 ^ %s + 7, ops =" % x, beam(y))
