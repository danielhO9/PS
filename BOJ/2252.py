import sys
input = sys.stdin.readline
import heapq

N, M = map(int, input().split())
graph = []
degree = [0] * (N + 1)
degree[0] = 1
for i in range(N + 1):
    graph.append([])
for i in range(M):
    start, end = map(int, input().split())
    graph[start].append(end)
    degree[end] += 1
arr = []
for i in range(N + 1):
    if degree[i] == 0:
        heapq.heappush(arr, i)
while arr:
    value = arr[0]
    heapq.heappop(arr)
    print(value, end = ' ')
    for i in graph[value]:
        degree[i] -= 1
        if degree[i] == 0:
            heapq.heappush(arr, i)