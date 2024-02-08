import sys
input = sys.stdin.readline

N = int(input())
A = list(map(int, input().split()))
arr, arr_reverse = [0] * N, [0] * N
arr[0], arr_reverse[-1] = 1, 1
for i in range(1, N):
    value = 0
    for j in range(i):
        if A[j] < A[i]:
            value = max(value, arr[j])
    arr[i] = value + 1
for i in range(N - 2, -1, -1):
    value = 0
    for j in range(i, N):
        if A[j] < A[i]:
            value = max(value, arr_reverse[j])
    arr_reverse[i] = value + 1
for i in range(N):
    arr[i] += arr_reverse[i] - 1
print(max(arr))

