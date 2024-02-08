# 64MB -> 1500만 개의 int가 아님
# 총 int 개수 : 500만 개

import sys
input = sys.stdin.readline
from collections import deque

n = int(input())
a, b, c = map(int, input().split())
x = list(map(int, input().split()))

X = [0]
for i in range(n):
    X.append(X[-1] + x[i])

# dp[i]는 i번째 병사까지 배치하는 최대 전투력(i번째에서 끊김)
# dp[i] = max(-2aXj * Xi + (aXj^2 - bXj + dp[j])) + (aXi^2 + bXi + c)
# 기울기 -2aXj는 계속 감소한다
# Xi = x0 + x1 + x2 + ... + xi (x0 = 0)

def meetPoint(line1, line2):
    return float((line2[1] - line1[1]) / (line1[0] - line2[0]))

# dp = [0]
graph = deque([[0, 0, 0]])
index = 0
for i in range(1, n + 1):
    # index를 조절
    while index != len(graph) - 1 and X[i] > graph[index + 1][2]:
        index += 1
    while index > 0:
        graph.popleft()
        index -= 1
    # dp 최신화
    # dp.append(graph[index][0] * X[i] + graph[index][1] + a * X[i] ** 2 + b * X[i] + c)
    # graph 최신화
    while graph[-1][2] >= meetPoint(graph[-1], [(-2) * a * X[i], a * X[i] ** 2 - b * X[i] + graph[index][0] * X[i] + graph[index][1] + a * X[i] ** 2 + b * X[i] + c]):
        if index == len(graph) - 1:
            index -= 1
        graph.pop()
    graph.append([(-2) * a * X[i], a * X[i] ** 2 - b * X[i] + graph[index][0] * X[i] + graph[index][1] + a * X[i] ** 2 + b * X[i] + c,
                  meetPoint(graph[-1], ((-2) * a * X[i], a * X[i] ** 2 - b * X[i] + graph[index][0] * X[i] + graph[index][1] + a * X[i] ** 2 + b * X[i] + c))])
    if i == n:
        print(graph[index][0] * X[i] + graph[index][1] + a * X[i] ** 2 + b * X[i] + c)