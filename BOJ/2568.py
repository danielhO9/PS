import sys
input = sys.stdin.readline
import bisect
from collections import deque

n = int(input())
lines = {}

for i in range(n):
    a, b = map(int, input().split())
    lines[b] = a
sorted_lines = sorted(lines.items(), key = lambda item: item[1])
arr = [sorted_lines[0][0]]
arr_index = [[0]]
for i in range(1, n):
    if sorted_lines[i][0] > arr[-1]:
        arr.append(sorted_lines[i][0])
        arr_index.append([i])
    else:
        index = bisect.bisect_left(arr, sorted_lines[i][0])
        arr[index] = sorted_lines[i][0]
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
print(n - len(answer))
pointer = 0
for i in range(n):
    if i != answer[pointer]:
        print(sorted_lines[i][1])
    else:
        pointer += 1
        if pointer == len(answer):
            pointer -= 1


# 8 2 9 1 4 6 7 10