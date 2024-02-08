import sys
input = sys.stdin.readline
from collections import deque

N = int(input())

def dfs(y, x):
    global answer
    global key
    if visited[y][x]:
        return
    queue = deque([[y, x]])
    while queue:
        place = deque.popleft(queue)
        visited[place[0]][place[1]] = True
        if arr[place[0]][place[1]] == '$':
            answer += 1
        if arr[place[0]][place[1]].islower() and arr[place[0]][place[1]] not in key:
            key += arr[place[0]][place[1]]
            if ord(arr[place[0]][place[1]].upper()) - 65 not in need:
                need.append(ord(arr[place[0]][place[1]].upper()) - 65)
        way = [[1, 0], [-1, 0], [0, 1], [0, -1]]
        for i in range(4):
            if 0 <= place[0] + way[i][0] <= h - 1 and 0 <= place[1] + way[i][1] <= w - 1 and not visited[place[0] + way[i][0]][place[1] + way[i][1]]:
                if arr[place[0] + way[i][0]][place[1] + way[i][1]].isupper():
                    if arr[place[0] + way[i][0]][place[1] + way[i][1]].lower() in key:
                        if [place[0] + way[i][0], place[1] + way[i][1]] not in queue:
                            queue.append([place[0] + way[i][0], place[1] + way[i][1]])
                    else:
                        if [place[0] + way[i][0], place[1] + way[i][1]] not in door[ord(arr[place[0] + way[i][0]][place[1] + way[i][1]]) - 65]:
                            door[ord(arr[place[0] + way[i][0]][place[1] + way[i][1]]) - 65].append([place[0] + way[i][0], place[1] + way[i][1]])
                else:
                    if [place[0] + way[i][0], place[1] + way[i][1]] not in queue:
                        queue.append([place[0] + way[i][0], place[1] + way[i][1]])

def solution(h, w):
    global answer
    global key
    for i in range(h):
        if i == 0 or i == h - 1:
            for j in range(w):
                if not arr[i][j].isupper() or (arr[i][j].isupper() and arr[i][j].lower() in key):
                    dfs(i, j)
                elif arr[i][j].isupper() and arr[i][j].lower() not in key:
                    door[ord(arr[i][j]) - 65].append([i, j])
        else:
            for j in range(2):
                if not arr[i][(w - 1) * j].isupper() or (arr[i][(w - 1) * j].isupper() and arr[i][(w - 1) * j].lower() in key):
                    dfs(i, (w - 1) * j)
                elif arr[i][(w - 1) * j].isupper() and arr[i][(w - 1) * j].lower() not in key:
                    door[ord(arr[i][(w - 1) * j]) - 65].append([i, (w - 1) * j])
    while need:
        possible = deque.popleft(need)
        while door[possible]:
            now = door[possible].pop()
            dfs(now[0], now[1])
    return answer

for i in range(N):
    answer = 0
    h, w = map(int, input().split())
    arr = []
    for i in range(h):
        arr.append(input().strip())
    key = input().strip()
    if key == '0':
        key = ''
    need = deque([])
    door = []
    for i in range(26):
        door.append([])
    visited = []
    for i in range(h):
        visited.append([False] * w)
    for i in range(h):
        for j in range(w):
            if arr[i][j] == "*":
                visited[i][j] = True
    print(solution(h, w))

# 시작하는 점이
# 복도인 경우 - 진행
# 문인 경우 - 진행할 수 있도록 가능한 경우에만 하도록 하자
# 열쇠인 경우 - key 먹고 진행
# $인 경우 - answer 키워주고 진행

# BFS 중에
# 복도인 경우 - 진행
# 열쇠인 경우 - 먹고 진행
# $인 경우 - 먹고 진행
# 문인 경우
# 키가 있는 경우 - 무시하고 진행
# 키가 없는 경우 - 진행 못함, door에 추가