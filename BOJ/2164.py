import sys
input = sys.stdin.readline
from collections import deque

N = int(input())
arr = deque()
for i in range(1, N + 1):
    arr.append(i)
cnt = 0
while len(arr) > 1:
    value = arr.popleft()
    if cnt % 2 != 0:
        arr.append(value)
    cnt += 1
print(arr[0])