import sys
import copy
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    arr.append(list(map(int, input().split())))
def up(arr):
    for i in range(N):
        line = []
        ans = []
        for j in range(N):
            if arr[j][i] != 0:
                line.append(arr[j][i])
        place = 0
        while place < len(line):
            if line[place] != 0:
                if place < len(line) - 1 and line[place] == line[place + 1]:
                    ans.append(line[place] * 2)
                    place += 1
                else:
                    ans.append(line[place])
            place += 1
        while len(ans) < N:
            ans.append(0)
        for j in range(N):
            arr[j][i] = ans[j]
def down(arr):
    for i in range(N):
        line = []
        ans = []
        for j in range(N):
            if arr[N - 1 - j][i] != 0:
                line.append(arr[N - 1 - j][i])
        place = 0
        while place < len(line):
            if line[place] != 0:
                if place < len(line) - 1 and line[place] == line[place + 1]:
                    ans.append(line[place] * 2)
                    place += 1
                else:
                    ans.append(line[place])
            place += 1
        while len(ans) < N:
            ans.append(0)
        for j in range(N):
            arr[N - 1 - j][i] = ans[j]
def left(arr):
    for i in range(N):
        line = []
        ans = []
        for j in range(N):
            if arr[i][j] != 0:
                line.append(arr[i][j])
        place = 0
        while place < len(line):
            if line[place] != 0:
                if place < len(line) - 1 and line[place] == line[place + 1]:
                    ans.append(line[place] * 2)
                    place += 1
                else:
                    ans.append(line[place])
            place += 1
        while len(ans) < N:
            ans.append(0)
        for j in range(N):
            arr[i][j] = ans[j]
def right(arr):
    for i in range(N):
        line = []
        ans = []
        for j in range(N):
            if arr[i][N - 1 - j] != 0:
                line.append(arr[i][N - 1 - j])
        place = 0
        while place < len(line):
            if line[place] != 0:
                if place < len(line) - 1 and line[place] == line[place + 1]:
                    ans.append(line[place] * 2)
                    place += 1
                else:
                    ans.append(line[place])
            place += 1
        while len(ans) < N:
            ans.append(0)
        for j in range(N):
            arr[i][N - 1 - j] = ans[j]
value = 0
def solution(arr, cnt):
    global value
    if cnt == 5:
        maximum = 0
        for i in range(N):
            maximum = max(maximum, max(arr[i]))
        value = max(maximum, value)
        return
    arr_0 = copy.deepcopy(arr)
    arr_1 = copy.deepcopy(arr)
    arr_2 = copy.deepcopy(arr)
    arr_3 = copy.deepcopy(arr)
    for i in range(4):
        if i == 0:
            up(arr_0)
            solution(arr_0, cnt + 1)
        elif i == 1:
            down(arr_1)
            solution(arr_1, cnt + 1)
        elif i == 2:
            left(arr_2)
            solution(arr_2, cnt + 1)
        else:
            right(arr_3)
            solution(arr_3, cnt + 1)
solution(arr, 0)

print(value)