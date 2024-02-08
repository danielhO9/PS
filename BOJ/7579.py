import sys
input = sys.stdin.readline

N, M = map(int, input().split())
m = list(map(int, input().split()))
c = list(map(int, input().split()))

sum_c = sum(c)
dp = []
for i in range(N):
    dp.append([0] * (sum_c + 1))
for i in range(sum_c + 1):
    if i >= c[0]:
        dp[0][i] = m[0]
for i in range(1, N):
    for j in range(sum_c + 1):
        if j >= c[i]:
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - c[i]] + m[i])
        else:
            dp[i][j] = dp[i - 1][j]
for i in range(sum_c + 1):
    if dp[-1][i] >= M:
        print(i)
        break
# M바이트 이상으로 메모리가 필요하며 그중 c의 값의 합이 최소가 되는 경우
# c를 기준으로 생각해보자.
# dp[앱의 번호][비용 c의 합 한도] -> 최대 m의 합
# F(C, i) = max(F(C, i - 1), F(C - ci, i - 1) + mi)