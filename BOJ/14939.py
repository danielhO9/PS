import sys
input = sys.stdin.readline

light = 0
for i in range(10):
    temp = input().strip()
    for j in range(10):
        if temp[j] == "O":
            light |= 1 << (100 - 10 * i - j - 1)

def switch(light, x):
    light ^= 1 << (x)
    if 0 <= x % 10 + 1 < 10:
        light ^= 1 << (x + 1)
    if 0 <= x % 10 - 1 < 10:
        light ^= 1 << (x - 1)
    if 0 <= x // 10 + 1 < 10:
        light ^= 1 << (x + 10)
    if 0 <= x // 10 - 1 < 10:
        light ^= 1 << (x - 10)
    return light

answer = 101
def do(light, cnt):
    # print(bin(light))
    global answer
    for i in range(1, 10):
        for j in range(10):
            if light | 1 << (10 * i - 10 + j) == light:
                cnt += 1
                light = switch(light, 10 * i + j)
    # print(bin(light))
    for i in range(10):
        if light | 1 << (90 + i) == light:
            return
    answer = min(answer, cnt)
    return

def solution(light, cnt, index):
    if index == 10:
        return
    do(light, cnt)
    solution(light, cnt, index + 1)

    light = switch(light, index)
    do(light, cnt + 1)
    solution(light, cnt + 1, index + 1)
solution(light, 0, 0)
if answer == 101:
    print(-1)
else:
    print(answer)