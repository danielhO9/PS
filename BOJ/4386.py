import sys
input = sys.stdin.readline
import math
import heapq

n = int(input())
stars = []
parent = []
for i in range(n):
    stars.append(list(map(float, input().split())))
    parent.append(i)

def find_parent(x):
    if parent[x] != x:
        return find_parent(parent[x])
    return x

def union_parent(a, b):
    a = find_parent(a)
    b = find_parent(b)
    parent[a], parent[b] = min(a, b), min(a, b)

graph = []
for i in range(n):
    for j in range(i + 1, n):
        heapq.heappush(graph, [math.sqrt((stars[j][1] - stars[i][1]) ** 2 + (stars[j][0] - stars[i][0]) ** 2), i, j])

answer = 0.0
while graph:
    new = heapq.heappop(graph)
    if find_parent(new[1]) != find_parent(new[2]):
        answer += new[0]
        union_parent(new[1], new[2])
print(answer)