import sys
input = sys.stdin.readline
from collections import deque

N, M = map(int, input().split())
arr = []
for i in range(N):
    arr.append(list(map(int, list(input().strip()))))
cnt = {1 : 0}
num = 2
way = [[0, 1], [-1, 0], [0, -1], [1, 0]]

def dfs(crd, num):
    global N, M
    cnt[num] = 0
    arr[crd[0]][crd[1]] = num
    queue = deque([crd])
    while queue:
        now = deque.popleft(queue)
        cnt[num] += 1
        for i in range(4):
            if 0 <= now[0] + way[i][0] < N and 0 <= now[1] + way[i][1] < M:
                if arr[now[0] + way[i][0]][now[1] + way[i][1]] == 0:
                    arr[now[0] + way[i][0]][now[1] + way[i][1]] = num
                    queue.append([now[0] + way[i][0], now[1] + way[i][1]])
for i in range(N):
    for j in range(M):
        if arr[i][j] == 0:
            dfs([i, j], num)
            num += 1
for i in range(N):
    answer = ''
    for j in range(M):
        if arr[i][j] != 1:
            answer += '0'
        else:
            value = 1
            next = []
            for k in range(4):
                if 0 <= i + way[k][0] < N and 0 <= j + way[k][1] < M and arr[i + way[k][0]][j + way[k][1]] not in next:
                    next.append(arr[i + way[k][0]][j + way[k][1]])
                    value += cnt[arr[i + way[k][0]][j + way[k][1]]]
            value %= 10
            answer += str(value)
    print(answer)