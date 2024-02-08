import sys
input = sys.stdin.readline
import math

def angle_bigger_90(v1, v2):
    dot_product = v1[0] * v2[0] + v1[1] * v2[1]
    if dot_product < 0:
        return True
    return False

def circumcenter(x1, y1, x2, y2, x3, y3):
    if angle_bigger_90([x2 - x1, y2 - y1], [x3 - x1, y3 - y1]):
        return([(x2 + x3) / 2, (y2 + y3) / 2, math.sqrt((x2 - x3) ** 2 + (y2 - y3) ** 2) / 2])
    if angle_bigger_90([x3 - x2, y3 - y2], [x1 - x2, y1 - y2]):
        return([(x3 + x1) / 2, (y3 + y1) / 2, math.sqrt((x3 - x1) ** 2 + (y3 - y1) ** 2) / 2])
    if angle_bigger_90([x1 - x3, y2 - y3], [x1 - x3, y2 - y3]):
        return([(x1 + x2) / 2, (y1 + y2) / 2, math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2) / 2])
    center = [
        ((x2 ** 2 - x3 ** 2 + y2 ** 2 - y3 ** 2) * (y1 - y2) - (x2 ** 2 - x1 ** 2 + y2 ** 2 - y1 ** 2) * (y3 - y2)) / (2 * (x1 - x2) * (y3 - y2) - 2 * (x3 - x2) * (y1 - y2)),
        ((y2 ** 2 - y3 ** 2 + x2 ** 2 - x3 ** 2) * (x1 - x2) - (y2 ** 2 - y1 ** 2 + x2 ** 2 - x1 ** 2) * (x3 - x2)) / (2 * (y1 - y2) * (x3 - x2) - 2 * (y3 - y2) * (x1 - x2))
    ]
    center.append(
        math.sqrt((center[0] - x1) ** 2 + (center[1] - y1) ** 2)
    )
    return center

def inCircle(x1, y1, x2, y2, x3, y3, a, b):
    center = circumcenter(x1, y1, x2, y2, x3, y3)
    if (center[0] - a) ** 2 + (center[1] - b) ** 2 > center[2] ** 2:
        return False
    return True

def solution():
    N = int(input())
    cordinates = []
    if N == 2:
        for _ in range(2):
            cordinates.append(list(map(int, input().split())))
        print(f'{(cordinates[0][0] + cordinates[1][0]) / 2:.3f}', end = " ")
        print(f'{(cordinates[0][1] + cordinates[1][1]) / 2:.3f}')
        print(f'{math.sqrt((cordinates[0][0] - cordinates[1][0]) ** 2 + (cordinates[0][1] - cordinates[1][1]) ** 2) / 2:.3f}')
        return
    for _ in range(N):
        cordinates.append(list(map(int, input().split())))
        if len(cordinates) > 3:
            if inCircle(cordinates[0][0], cordinates[0][1], cordinates[1][0], cordinates[1][1], cordinates[2][0], cordinates[2][1], cordinates[3][0], cordinates[3][1]):
                cordinates.pop()
            else:
                size = 90000.0
                answer = []
                # i는 포함되지 않는 점 index
                for i in range(3):
                    # 포함될 점이 저장될 공간
                    temp = []
                    for j in range(4):
                        if j != i:
                            temp.append(cordinates[j])
                    temp_center = circumcenter(temp[0][0], temp[0][1], temp[1][0], temp[1][1], temp[2][0], temp[2][1])
                    if (cordinates[i][0] - temp_center[0]) ** 2 + (cordinates[i][1] - temp_center[1]) ** 2 <= \
                            temp_center[2] ** 2 and size > temp_center[2]:
                        size = temp_center[2]
                        answer = temp
                cordinates = answer
    answer_center = circumcenter(cordinates[0][0], cordinates[0][1], cordinates[1][0], cordinates[1][1], cordinates[2][0], cordinates[2][1])
    print(cordinates)
    print(f'{answer_center[0]:.3f}', end=" ")
    print(f'{answer_center[1]:.3f}')
    print(f'{answer_center[2]:.3f}')
solution()