import sys
input = sys.stdin.readline
from collections import deque

# land에 땅을 저장하되 필요없는 땅들은 걸러낸다.
N = int(input())
arr = [list(map(int, input().split())) for _ in range(N)]
arr.sort()
land = []
temp = arr[0]
for i in range(N):
    if temp[0] == arr[i][0]:
        temp[1] = arr[i][1]
    else:
        while land and land[-1][1] <= temp[1]:
            land.pop()
        land.append(temp)
        temp = arr[i]
    if i == N - 1:
        while land and land[-1][1] <= temp[1]:
            land.pop()
        land.append(temp)
# dp[i] : i번째 땅까지 사는 최소 비용(dp[0] = 0)
# dp[i] = min(dp[j] + land[j][1] * land[i - 1][0])(0 <= j <= i - 1)
# dp[1] = min(dp[0] + land[0][1] * land[0][0])

def meetPoint(line1, line2):
    return (line2[1] - line1[1]) / (line1[0] - line2[0])

dp = [0]
graph = deque([[land[0][1], 0, 0]])
index = 0
for i in range(1, len(land) + 1):
    # index 조정
    while index != len(graph) - 1 and graph[index + 1][2] < land[i - 1][0]:
        index += 1
    while index > 0:
        graph.popleft()
        index -= 1
    dp.append(graph[index][0] * land[i - 1][0] + graph[index][1])
    if i == len(land):
        print(dp[i])
        break
    while graph[-1][2] >= meetPoint(graph[-1], [land[i][1], dp[i]]):
        if index == len(graph) - 1:
            index -= 1
        graph.pop()
    graph.append([land[i][1], dp[i], meetPoint(graph[-1], [land[i][1], dp[i]])])