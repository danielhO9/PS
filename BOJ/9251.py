import sys
input = sys.stdin.readline

A = input().strip()
B = input().strip()

dp = []
for i in range(len(A) + 1):
    dp.append([0] * (len(B) + 1))
for i in range(len(A) + 1):
    for j in range(len(B) + 1):
        if i == 0 or j == 0:
            dp[i][j] = 0
        elif A[i - 1] == B[j - 1]:
            dp[i][j] = dp[i - 1][j - 1] + 1
        else:
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
print(dp[len(A)][len(B)])
ans = ''
count = 0
x, y = len(B), len(A)
while count < dp[len(A)][len(B)]:
    if dp[y][x] > dp[y - 1][x - 1] and dp[y][x] > dp[y - 1][x] and dp[y][x] > dp[y][x - 1]:
        count += 1
        ans = B[x - 1] + ans
        x -= 1
        y -= 1
    elif dp[y][x] == dp[y][x - 1]:
        x -= 1
    else:
        y -= 1
print(ans)