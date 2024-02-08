import sys
input = sys.stdin.readline

n = int(input())

# distance[i] : i와 1 사이의 거리(i > 1)
distance = [0 for _ in range(n + 1)]
temp = list(map(int, input().split()))
for i in range(n - 1):
    distance[i + 2] = distance[i + 1] + temp[i]
print(distance)

# p[i], s[i]는 i 행성의 정보
p, s = [0 for _ in range(n)], [0 for _ in range(n)]
for i in range(n - 1):
    p[i + 1], s[i + 1] = map(int, input().split())

# dp[i] : i 행성까지 가는 최단시간
# dp[i] = min(dp[j] + (distance[i] - distance[j]) * s[j] + p[j])
# dp[i] = min(s[j] * distance[i] + dp[j] + p[j] - distance[j] * s[j]) (1 <= j < i)
dp = [0 for _ in range(n + 1)]
graph = []