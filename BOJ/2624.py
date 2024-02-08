import sys
input = sys.stdin.readline

T = int(input())
k = int(input())

# dp[i][j] -> i가지의 동전을 사용하여 j의 금액을 바꾸는 경우의 수
dp = [[0] * (T + 1)]

# i는 사용하는 동전의 가지수
for i in range(1, k + 1):
    p, n = map(int, input().split())
    dp.append([0] * (T + 1))
    for j in range(1, n + 1):
        if p * j <= T:
            dp[i][p * j] = 1
    for j in range(T + 1):
        for l in range(n + 1):
            if j + p * l <= T:
                dp[i][j + p * l] += dp[i - 1][j]
print(dp[-1][-1])
print(dp)