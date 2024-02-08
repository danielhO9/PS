import sys
import bisect
from collections import deque
input = sys.stdin.readline

N, S = map(int, input().split())
arr1 = list(map(int, input().split()))
arr2, sum1, sum2 = [], [], []
answer = 0
for i in range(len(arr1) // 2):
    arr2.append(arr1.pop())
queue1 = deque([[0, 1], [arr1[0], 1]])
while queue1:
    now = queue1.pop()
    if now[1] == len(arr1):
        sum1.append(now[0])
    else:
        now[1] += 1
        queue1.append(now)
        now_copy = now.copy()
        now_copy[0] += arr1[now_copy[1] - 1]
        queue1.append(now_copy)
if len(arr2) > 0:
    queue2 = deque([[0, 1], [arr2[0], 1]])
    while queue2:
        now = queue2.pop()
        if now[1] == len(arr2):
            sum2.append(now[0])
        else:
            now[1] += 1
            queue2.append(now)
            now_copy = now.copy()
            now_copy[0] += arr2[now_copy[1] - 1]
            queue2.append(now_copy)
sum1.sort()
for i in sum2:
    answer += bisect.bisect_right(sum1, S - i) - bisect.bisect_left(sum1, S - i)
if N > 1:
    if S == 0:
        print(answer - 1)
    else:
        print(answer)
else:
    if arr1[0] == S:
        print(1)
    else:
        print(0)