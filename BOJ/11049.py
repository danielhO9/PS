import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    arr.append(list(map(int, input().split())))
dp = []
for i in range(N):
    dp.append([])
    for j in range(N - i):
        if j == 0:
            dp[-1].append([arr[i][0], arr[i][1], 0])
        else:
            dp[-1].append([0, 0, 2 ** 31])
for i in range(1, N):
    for j in range(N - i):
        for k in range(j + 1, j + i + 1):
            if dp[j][i][2] > dp[j][k - j - 1][2] + dp[k][i + j - k][2] + dp[j][k - j - 1][0] * dp[j][k - j - 1][1] * dp[k][i + j - k][1]:
                dp[j][i][2] = dp[j][k - j - 1][2] + dp[k][i + j - k][2] + dp[j][k - j - 1][0] * dp[j][k - j - 1][1] * dp[k][i + j - k][1]
                dp[j][i][0], dp[j][i][1] = [dp[j][k - j - 1][0], dp[k][i + j - k][1]]
print(dp[0][-1][-1])
# 두 개짜리 곱 -> 499개
# 세 개짜리 곱 -> 498개
# 500개짜리 곱 -> 1개