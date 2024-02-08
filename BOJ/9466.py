import sys
input = sys.stdin.readline

def solution(n, arr):
    degree = [0] * (n + 1)
    degree[0] = 1
    for i in arr:
        degree[i] += 1
    now = []
    for i in range(n + 1):
        if degree[i] == 0:
            now.append(i)
    cnt = 0
    while now:
        value = now.pop()
        cnt += 1
        degree[arr[value - 1]] -= 1
        if degree[arr[value - 1]] == 0:
            now.append(arr[value - 1])
    return cnt
T = int(input())
for i in range(T):
    n = int(input())
    arr = list(map(int, input().split()))
    print(solution(n, arr))