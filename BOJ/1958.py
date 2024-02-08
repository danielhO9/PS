import sys
input = sys.stdin.readline

A = input().strip()
B = input().strip()
C = input().strip()

dp = []
for i in range(len(A) + 1):
    dp.append([])
    for j in range(len(B) + 1):
        dp[-1].append([0] * (len(C) + 1))
for i in range(len(A) + 1):
    for j in range(len(B) + 1):
        for k in range(len(C) + 1):
            if i == 0 or j == 0 or k == 0:
                dp[i][j][k] = 0
            elif A[i - 1] == B[j - 1] == C[k - 1]:
                dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1
            else:
                dp[i][j][k] = max(dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1])
print(dp[-1][-1][-1])