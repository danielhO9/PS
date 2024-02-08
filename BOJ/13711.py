import sys
input = sys.stdin.readline
import bisect

N = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))
dict = {}
for i in range(N):
    dict[B[i]] = i
arr = []
for i in A:
    arr.append(dict[i])
now = [arr[0]]
for i in range(1, N):
    if now[-1] < arr[i]:
        now.append(arr[i])
    else:
        index = bisect.bisect_left(now, arr[i])
        now[index] = arr[i]
print(len(now))
# 1 0
# 0 2 1