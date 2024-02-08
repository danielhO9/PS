import sys
input = sys.stdin.readline
import math

N, M = map(int, input().split())
arr = []
for i in range(N):
    V, C, K = map(int, input().split())
    cnt = math.floor(math.log2(K + 1))
    for j in range(cnt):
        arr.append([V * (2 ** j), C * (2 ** j)])
    if K - (2 ** cnt - 1) != 0:
        arr.append([V * (K - (2 ** cnt - 1)), C * (K - (2 ** cnt - 1))])

dp = []
for i in range(len(arr)):
    dp.append([0] * (M + 1))

for i in range(len(arr)):
    if i == 0:
        for j in range(1, M + 1):
            if arr[i][0] <= j:
                dp[i][j] = arr[i][1]
    else:
        for j in range(1, M + 1):
            if arr[i][0] <= j:
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - arr[i][0]] + arr[i][1])
            else:
                dp[i][j] = dp[i - 1][j]
print(dp[len(arr) - 1][M])
# 시간 복잡도 : 10 ** 10
# 여러개 있는 물건을 바꾼다면 -> 물건이 총 14000000
# 1부터 2 ** N - 2 까지 -> 1, 2, 2 ** 2 ... 2 ** (N - 2)