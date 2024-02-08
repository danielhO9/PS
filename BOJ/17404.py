import sys
input = sys.stdin.readline

N = int(input())
R, G, B = [], [], []
for i in range(N):
    arr = list(map(int, input().split()))
    R.append(arr[0])
    G.append(arr[1])
    B.append(arr[2])
arr = [R, G, B]

dp = [[[10 ** 6, 10 ** 6, 10 ** 6], [10 ** 6, 10 ** 6, 10 ** 6], [10 ** 6, 10 ** 6, 10 ** 6]], [[10 ** 6, arr[0][0] + arr[1][1], arr[0][0] + arr[2][1]], [arr[1][0] + arr[0][1], 10 ** 6, arr[1][0] + arr[2][1]], [arr[2][0] + arr[0][1], arr[2][0] + arr[1][1], 10 ** 6]]]
for i in range(3, N + 1):
    dp.append([[10 ** 6, 10 ** 6, 10 ** 6], [10 ** 6, 10 ** 6, 10 ** 6], [10 ** 6, 10 ** 6, 10 ** 6]])
for i in range(1, N - 1):
    for j in range(3):
        for k in range(3):
            dp[i + 1][j][(k + 1) % 3] = min(dp[i][j][k] + arr[(k + 1) % 3][i + 1], dp[i + 1][j][(k + 1) % 3])
            dp[i + 1][j][(k - 1) % 3] = min(dp[i][j][k] + arr[(k - 1) % 3][i + 1], dp[i + 1][j][(k - 1) % 3])
answer = []
for i in range(3):
    for j in range(3):
        if i != j:
            answer.append(dp[-1][i][j])
print(min(answer))