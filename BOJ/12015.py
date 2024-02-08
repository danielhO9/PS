import sys
input = sys.stdin.readline
import bisect

N = int(input())
A = list(map(int, input().split()))

arr = [A[0]]
for i in range(1, len(A)):
    if A[i] > arr[-1]:
        arr.append(A[i])
    else:
        index = bisect.bisect_left(arr, A[i])
        arr[index] = A[i]
print(len(arr))