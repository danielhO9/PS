import sys
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 6)

N = int(input())
# vertex에 트리 저장
vertex = [{} for _ in range(N + 1)]
for _ in range(N - 1):
    U, V, D = map(int, input().split())
    vertex[U][V] = D
    vertex[V][U] = D

# S[i], V[i]는 i 도시의 전령 정보
S, V = [0] * (N + 1), [0] * (N + 1)
for i in range(N - 1):
    s, v = map(int, input().split())
    S[i + 2], V[i + 2] = s, v

# DFS를 재귀함수를 통해 진행하자
# DFS의 마지막에 graph를 복귀시켜주면 된다.
# 방금 바꾼 그 하나만 복귀시키면 된다.
# 따로 저장해두고, 다시 불러오는 과정은 시간, 메모리 초과할 듯
# graph에 하나 추가하면 graph의 크기와 graph의 마지막 값 변경됨
# graph 크기는 lenght로 저장한다.

# dp[i] = min(-D[j] x V[i] + dp[j]) + S[i] + D[i] x V[i]
distance = [0] * (N + 1)

# child만 저장, (기울기, y절편) -> (-distance[i], dp[i])
graph, lenght = [0] * N, 0
visited = [False] * (N + 1)
dp = [0] * (N + 1)

def meetPoint(a, b):
    return (dp[b] - dp[a]) / (-distance[a] + distance[b])

def dfs(child, parent):
    global lenght
    visited[child] = True
    temp = []
    if child == 1:
        graph[0] = 1
    else:
        distance[child] = distance[parent] + vertex[parent][child]
        start, end, mid = 0, lenght, 0
        while start <= end:
            mid = (start + end) // 2
            if start == end:
                break
            if meetPoint(graph[mid], graph[mid + 1]) <= V[child]:
                start = mid + 1
            else:
                end = mid
        dp[child] = -distance[graph[mid]] * V[child] + dp[graph[mid]] + S[child] + distance[child] * V[child]

        start, end, mid = 0, lenght, 0
        while start <= end:
            mid = (start + end) // 2
            if start == end:
                break
            if meetPoint(graph[mid], graph[mid + 1]) < meetPoint(graph[mid], child):
                start = mid + 1
            else:
                end = mid
        temp.append(lenght)
        lenght = mid + 1
        temp.append([lenght, graph[lenght]])
        graph[lenght] = child
        if distance[graph[lenght]] == distance[graph[lenght - 1]]:
            lenght = temp[0]
            graph[temp[1][0]] = temp[1][1]
            temp.clear()

    for i in vertex[child].keys():
        if not visited[i]:
            dfs(i, child)
            visited[i] = True
    if temp:
        lenght = temp[0]
        graph[temp[1][0]] = temp[1][1]

dfs(1, 0)
for i in range(N - 1):
    print(dp[i + 2], end = " ")
'''
5
1 2 20
2 3 12
2 4 0
4 5 3
26 9
1 10
500 2
2 30
'''