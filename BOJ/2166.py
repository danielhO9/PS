import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    arr.append(list(map(int, input().split())))
arr.append(arr[0])
value1, value2 = 0, 0
for i in range(N):
    value1 += arr[i][0] * arr[i + 1][1]
    value2 += arr[i][1] * arr[i + 1][0]
print(round(abs(value1 - value2) / 2, 1))