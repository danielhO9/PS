import sys
from collections import deque
input = sys.stdin.readline

N, M = map(int, input().split())
map = []
map_start = []
map_end = []
for i in range(N):
    line = input()
    map.append([])
    map_start.append([])
    map_end.append([])
    for j in range(M):
        map[-1].append(int(line[j]))
        map_start[-1].append(int(line[j]))
        map_end[-1].append(int(line[j]))

def solution(map, index):
    queue = deque([index])
    map[index // M][index % M] = 11
    while queue:
        now = queue.popleft()
        dx, dy = [1, -1, 0, 0], [0, 0, 1, -1]
        for i in range(4):
            if 0 <= now // M + dx[i] < N and 0 <= now % M + dy[i] < M:
                if map[now // M + dx[i]][now % M + dy[i]] == 0:
                    queue.append(now + M * dx[i] + dy[i])
                    map[now // M + dx[i]][now % M + dy[i]] = map[now // M][now % M] + 1

solution(map_start, 0)
solution(map_end, N * M - 1)

arr = []
for i in range(N):
    for j in range(M):
        if map[i][j] == 1:
            arr_start, arr_end = [], []
            dx, dy = [1, -1, 0, 0], [0, 0, 1, -1]
            for k in range(4):
                if 0 <= i + dx[k] < N and 0 <= j + dy[k] < M:
                    if map_start[i + dx[k]][j + dy[k]] > 10:
                        arr_start.append(map_start[i + dx[k]][j + dy[k]])
                    if map_end[i + dx[k]][j + dy[k]] > 10:
                        arr_end.append(map_end[i + dx[k]][j + dy[k]])
            if arr_start and arr_end:
                arr.append(min(arr_start) + min(arr_end) - 19)
if map_start[-1][-1] == 0:
    if len(arr) == 0:
        print(-1)
    else:
        print(min(arr))
else:
    arr.append(map_start[-1][-1] - 10)
    print(min(arr))