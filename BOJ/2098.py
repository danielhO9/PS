import sys
input = sys.stdin.readline

N = int(input())
W = []
for i in range(N):
    W.append(list(map(int, input().split())))
dp = []
for i in range(N):
    dp.append([16000001] * (2 ** N))
for i in range(1, N):
    if W[0][i] != 0:
        dp[i][1 | 1 << i] = W[0][i]
    else:
        dp[i][1 | 1 << i] = 16000002

def min_value(now, visit):
    if dp[now][visit] != 16000001:
        return dp[now][visit]
    if now == 0:
        for i in range(1, N):
            dp[i][2 ** N - 1] = min_value(i, 2 ** N - 1)
            if W[i][now] != 0:
                dp[now][visit] = min(dp[now][visit], dp[i][2 ** N - 1] + W[i][now])
        return dp[now][visit]
    switch = False
    for i in range(1, N):
        if visit & ~(1 << now) == visit & ~(1 << now) | (1 << i):
            dp[i][visit & ~(1 << now)] = min_value(i, visit & ~(1 << now))
            if dp[i][visit & ~(1 << now)] != 16000002 and W[i][now] != 0:
                switch = True
                dp[now][visit] = min(dp[now][visit], dp[i][visit & ~(1 << now)] + W[i][now])
    if not switch:
        dp[now][visit] = 16000002
    return dp[now][visit]
print(min_value(0, 1))






# 순환이 있으므로 어디서 시작하든 상관없다.
# 도시 번호는 0번부터 N - 1번으로.
# 0번에서 출발한다 하자.
# 거쳤는지 여부는 비트를 통해 표현한다. [현재 위치, 지난 도시]
# [0, 0001]
# [1, 0011],            [2, 0101],            [3, 1001]
# [2, 0111], [3, 1011], [1, 0111], [3, 1101], [1, 1011], [2, 1101]
# [3, 1111], [2, 1111], [3, 1111], [1, 1111], [2, 1111], [1, 1111]