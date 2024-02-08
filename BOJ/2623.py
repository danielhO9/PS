import sys
input = sys.stdin.readline

def solution():
    N, M = map(int, input().split())
    graph, degree = [], [0] * (N + 1)
    degree[0] = 1
    for i in range(N + 1):
        graph.append([])
    for i in range(M):
        arr = list(map(int, input().split()))
        for j in range(1, arr[0]):
            graph[arr[j]].append(arr[j + 1])
            degree[arr[j + 1]] += 1
    arr = []
    for i in range(N + 1):
        if degree[i] == 0:
            arr.append(i)
    if len(arr) == 0:
        return [0]
    ans = []
    visited = [False] * (N + 1)
    while arr:
        now = arr.pop()
        if visited[now] == True:
            return [0]
        for i in graph[now]:
            degree[i] -= 1
            if degree[i] == 0:
                arr.append(i)
        visited[now] = True
        ans.append(now)
    if len(ans) == N:
        return ans
    return [0]
arr = solution()
for i in arr:
    print(i)