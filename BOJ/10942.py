import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
dp = []
for i in range(N):
    dp.append([-1] * (N - i))
for i in range(N):
    dp[i][0] = 1
    if i < N - 1:
        if arr[i] == arr[i + 1]:
            dp[i][1] = 1
        else:
            dp[i][1] = 0

def palindrome(S, E):
    if dp[S - 1][E - S] != -1:
        return dp[S - 1][E - S]
    if arr[S - 1] != arr[E - 1]:
        dp[S - 1][E - S] = 0
        return 0
    else:
        dp[S][E - S - 2] = palindrome(S + 1, E - 1)
        return dp[S][E - S - 2]

M = int(input())
for i in range(M):
    S, E = map(int, input().split())
    print(palindrome(S, E))