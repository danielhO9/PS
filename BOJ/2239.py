import sys
input = sys.stdin.readline

arr = []
for i in range(9):
    value = input()
    for j in value[:9]:
        arr.append(int(j))

def check(place, value):
    x, y = place % 9, place // 9
    for i in range(9):
        if arr[9 * i + x] == value:
            return False
    for i in range(9):
        if arr[9 * y + i] == value:
            return False
    for i in range(3):
        for j in range(3):
            if arr[9 * ((y // 3) * 3 + j) + (x // 3) * 3 + i] == value:
                return False
    return True
def solution(x):
    if 0 not in arr:
        for i in range(9):
            for j in range(9):
                print(arr[9 * i + j], end = '')
            if i != 8:
                print()
        sys.exit()
    if arr[x] == 0:
        impossible = True
        for i in range(1, 10):
            if check(x, i):
                impossible = False
                arr[x] = i
                solution(x + 1)
                arr[x] = 0
        if impossible:
            return
    else:
        solution(x + 1)
solution(0)