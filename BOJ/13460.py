import sys
input = sys.stdin.readline
from collections import deque

N, M = map(int, input().split())
board = []
for i in range(N):
    board.append(list(input().strip()))
for i in range(N):
    for j in range(M):
        if board[i][j] == "R":
            red = [i, j]
            board[i][j] = "."
        elif board[i][j] == "B":
            blue = [i, j]
            board[i][j] = "."

def move(target, another, way):
    four = [[0, 1], [-1, 0], [0, -1], [1, 0]]
    while 1 <= target[0] + four[way][0] <= N - 2 and 1 <= target[1] + four[way][1] <= M - 2 and board[target[0] + four[way][0]][target[1] + four[way][1]] == "." and (target[0] + four[way][0] != another[0] or target[1] + four[way][1] != another[1]):
        target[0] += four[way][0]
        target[1] += four[way][1]
    if board[target[0] + four[way][0]][target[1] + four[way][1]] == 'O':
        return [0, 0]
    return [target[0], target[1]]

def tilt(red, blue, way):
    red = move(red, blue, way)
    blue = move(blue, red, way)
    if blue == [0, 0]:
        return False
    if red == [0, 0]:
        return True
    red = move(red, blue, way)
    if red == [0, 0]:
        return True
    return red, blue, way

def solution():
    queue = deque([])
    for i in range(4):
        red_copy, blue_copy = red.copy(), blue.copy()
        if type(tilt(red_copy, blue_copy, i)) == bool:
            if tilt(red_copy, blue_copy, i):
                return 1
            else:
                continue
        else:
            red_copy, blue_copy, way = tilt(red_copy, blue_copy, i)
            for j in range(4):
                if j != way:
                    red_copy_copy, blue_copy_copy = red_copy.copy(), blue_copy.copy()
                    queue.append([red_copy_copy, blue_copy_copy, j, 1])
    while queue:
        now = queue.popleft()
        red_copy, blue_copy, way, cnt = now[0], now[1], now[2], now[3]
        if cnt == 10:
            continue
        if type(tilt(red_copy, blue_copy, way)) == bool:
            if tilt(red_copy, blue_copy, way):
                return cnt + 1
            else:
                continue
        else:
            red_copy, blue_copy, way = tilt(red_copy, blue_copy, way)
            for j in range(4):
                if j != way:
                    red_copy_copy, blue_copy_copy = red_copy.copy(), blue_copy.copy()
                    queue.append([red_copy_copy, blue_copy_copy, j, cnt + 1])
    return -1
print(solution())

# 3 ** 9 * 4 = 78732
# 만약 red와 blue가 기울이는 방향으로 같은 줄에 있다면
# red와 blue를 red, blue, red로 움직이면 된다.
