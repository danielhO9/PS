import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(101):
    arr.append([])
    for j in range(10):
        arr[i].append([0] * 1024)
for i in range(1, 10):
    arr[1][i][1 << i] = 1
for n in range(1, 100):
    for now in range(0, 10):
        for visited in range(1024):
            if arr[n][now][visited] != 0:
                if now < 9:
                    arr[n + 1][now + 1][visited | 1 << (now + 1)] += arr[n][now][visited]
                if now > 0:
                    arr[n + 1][now - 1][visited | 1 << (now - 1)] += arr[n][now][visited]
answer = 0
for i in range(10):
    answer += arr[N][i][1023]
print(answer % 1000000000)
# 0000000000이 10개 -> N개
# 1024000
# arr[N][현재 위치][비트]
# arr[N][0][비트] = arr[N - 1][1][비트]
# arr[N][1][비트] = arr[N - 1][0][비트] + arr[N - 1][2][비트]