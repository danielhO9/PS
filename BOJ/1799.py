import sys
input = sys.stdin.readline

size = int(input())
arr = []
for i in range(size):
    arr.append(list(map(int, input().split())))

min_x1, min_y1, min_x2, min_y2 = 0, 0, 0, 0
for i in range(size ** 2 - 1, -1, -1):
    if (i // size + i % size) % 2 == 0:
        if arr[i // size][i % size] == 1:
            min_x1, min_y1 = i % size, i // size
            break
for i in range(size ** 2 - 1, -1, -1):
    if (i // size + i % size) % 2 == 1:
        if arr[i // size][i % size] == 1:
            min_x2, min_y2 = i % size, i // size
            break
answer1, answer2 = 0, 0
plus1, minus1, plus2, minus2 = [], [], [], []
def solution1(value):
    global answer1
    if value % size == min_x1 and value // size == min_y1:
        answer1 = max(answer1, len(plus1))
        return
    for i in range(value, size * min_y1 + min_x1 + 1):
        x, y = i % size, i // size
        if (value % size + value // size) % 2 == (x + y) % 2:
            if arr[y][x] == 1 and x + y not in plus1 and x - y not in minus1:
                plus1.append(x + y)
                minus1.append(x - y)
                solution1(i)
                plus1.pop()
                minus1.pop()
def solution2(value):
    global answer2
    if value % size == min_x2 and value // size == min_y2:
        answer2 = max(answer2, len(plus2))
        return
    for i in range(value, size * min_y2 + min_x2 + 1):
        x, y = i % size, i // size
        if (value % size + value // size) % 2 == (x + y) % 2:
            if arr[y][x] == 1 and x + y not in plus2 and x - y not in minus2:
                plus2.append(x + y)
                minus2.append(x - y)
                solution2(i)
                plus2.pop()
                minus2.pop()
solution1(0)
solution2(1)
print(answer1 + answer2)
'''
5
0 0 0 0 0
0 1 0 1 0
1 0 0 0 1
0 1 0 1 0
0 0 0 0 0
    if value % size == min_x2 and value // size == min_y2:
        answer1 = max(answer1, len(plus))
        return
'''