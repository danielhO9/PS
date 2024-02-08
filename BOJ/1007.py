import sys
input = sys.stdin.readline
from collections import deque
import math

T = int(input())

def case_minus(N):
    arr = []
    queue = deque([[[], 0]])
    while queue:
        now = queue.popleft()
        if len(now[0]) == int(N / 2):
            arr.append(now[0])
            continue
        if N - now[1] + len(now[0]) == int(N / 2):
            tmp = now[0].copy()
            tmp.append(now[1])
            queue.append([tmp, now[1] + 1])
        elif N - now[1] + len(now[0]) > int(N / 2):
            queue.append([now[0], now[1] + 1])
            tmp = now[0].copy()
            tmp.append(now[1])
            queue.append([tmp, now[1] + 1])
    return arr

def solution():
    N = int(input())
    X, Y = [], []
    answer = []
    for i in range(N):
        x, y = map(int, input().split())
        X.append(x)
        Y.append(y)
    minus = case_minus(N)
    for case in minus:
        answer_x, answer_y = 0, 0
        for i in range(N):
            if i in case:
                answer_x -= X[i]
                answer_y -= Y[i]
            else:
                answer_x += X[i]
                answer_y += Y[i]
        answer.append(answer_x ** 2 + answer_y ** 2)
    return min(answer)
final = []
for i in range(T):
    value = solution()
    final.append(math.sqrt(value))
for i in final:
    print(i)