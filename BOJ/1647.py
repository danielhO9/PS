import sys
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 5)

N, M = map(int, input().split())
edges = []
for i in range(M):
    edge = list(map(int, input().split()))
    edges.append(edge)
if N == 2:
    print(0)
else:
    edges.sort(key=lambda x: x[2])
    answer = 0
    parent = []
    for i in range(N + 1):
        parent.append(i)
    edge_count = 0

    def find_parent(x):
        if parent[x] == x:
            return x
        return find_parent(parent[x])

    def union_parent(edge):
        global answer
        global edge_count
        x = find_parent(edge[0])
        y = find_parent(edge[1])
        if x != y:
            parent[x], parent[y] = min(x, y), min(x, y)
            answer += edge[2]
            edge_count += 1

    for edge in edges:
        union_parent(edge)
        if edge_count == N - 2:
            break
    print(answer)