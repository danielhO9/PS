import sys
input = sys.stdin.readline
import bisect
from collections import deque

N = int(input())
A = list(map(int, input().split()))

arr = [A[0]]
arr_index = [[0]]
for i in range(1, len(A)):
    if A[i] > arr[-1]:
        arr.append(A[i])
        arr_index.append([i])
    else:
        index = bisect.bisect_left(arr, A[i])
        arr[index] = A[i]
        arr_index[index].append(i)

answer = deque([])
value = arr_index[-1][-1]
for i in range(len(arr) - 1, -1, -1):
    if i == len(arr) - 1:
        answer.append(value)
    else:
        index = bisect.bisect(arr_index[i], value) - 1
        value = arr_index[i][index]
        answer.appendleft(value)
print(arr)
print(len(answer))
for i in answer:
    print(A[i], end = ' ')

# 10 20 10 30 20 50 80 25 15 40 50 15 90 20 25 30
# 5  10 15 20 30 90

# 0  1  3  5  6  12 22
# 2  4  7  9  10 21
#    8  13 14 15
# 16 11 18 19 20
#    17