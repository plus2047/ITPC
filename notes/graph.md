GRAPH is used to describe nodes with relationship with each other.

We know, this is a graph:

```
* -- * -- *
\  /
  * -- *
```

But be careful, some other things such as a GRID is also a GRAPH.

```
 - - - - -
| | | | | |
 - - - - -
| | | | | |
 - - - - -
```

GRAPH can also be used to describe status(nodes) and transitions(edges).

GRAPH is the most common data struct we know,
so if we meet a hard question with complex status & transitions,
or it's a question about grid, think about GRAPH.

## shortest path problem

for UN-WEIGHTED graph (all edges have the same ds):
BFS

for POSITIVE-WEIGHTED directional / un-directional graph:
Dijkstra's algorithm (single-source shortest path_from)

if NEGATIVE-WEIGHTED edge exist:
Bellman-Ford algorithm.

if need to get shortest path len between EACH NODE:
Floyd's algorithm.

floyd's algorithm can run on graph with negative edge.
but it cannot detect negative circle.
if negative circle exist between node i & j,
flody's result for shortest_path(i, j) will be meaningless.
but flody can still get currect result for other node pair.
