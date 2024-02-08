import sys
input = sys.stdin.readline

R, C, M = map(int, input().split())
# 상어 10000마리, 사람 위치 100 -> 1000000번 연산

answer = 0
alivedShark = [False] * 10001
data = {}
for i in range(M):
    r, c, s, d, z = map(int, input().split())
    data[z] = [r, c, s, d]
    alivedShark[z] = True

def placeCal(r, c, s, d, n):
    # 1, 2, 3, 4 -> 위, 아래, 오른쪽, 왼쪽
    direction = [[0, 0], [-1, 0], [1, 0], [0, 1], [0, -1]]
    return_r = r + direction[d][0] * s * (n - 1)
    return_c = c + direction[d][1] * s * (n - 1)
    return_r %= 2 * R - 2
    return_c %= 2 * C - 2
    if return_r == 0:
        return_r = 2
    elif return_r > R:
        return_r = 2 * R - return_r
    if return_c == 0:
        return_c = 2
    elif return_c > C:
        return_c = 2 * C - return_c
    return return_r, return_c

for person in range(1, C + 1):
    tempArr = []
    for i in range(R + 1):
        tempArr.append([0] * (C + 1))
    getPlace = R + 1
    tempAnswer = 0
    for sharkIndex in range(len(alivedShark)):
        if alivedShark[sharkIndex]:
            temp_r, temp_c = placeCal(data[sharkIndex][0], data[sharkIndex][1], data[sharkIndex][2], data[sharkIndex][3], person)
            if tempArr[temp_r][temp_c] != 0:
                alivedShark[tempArr[temp_r][temp_c]] = False
            tempArr[temp_r][temp_c] = sharkIndex
            if temp_c == person and temp_r <= getPlace:
                getPlace = temp_r
                tempAnswer = sharkIndex
    answer += tempAnswer
    alivedShark[tempAnswer] = False
print(answer)