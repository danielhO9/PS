import sys
input = sys.stdin.readline

arr = list(map(int, input().split()))
point = []

def judge(x, y):
    if x == 0 or y == 0:
        return 2
    if x % 2 == y % 2:
        return 4
    else:
        return 3

for i in range(len(arr) - 1):
    point.append([4000000] * 5)
if arr[0] == 0:
    print(0)
else:
    point[0][0] = 2
    for i in range(len(arr) - 2):
        # arr[i], j
        # arr[i + 1], 0 ~ 4
        for j in range(5):
            if point[i][j] != 4000000:
                if arr[i] == arr[i + 1]:
                    point[i + 1][j] = min(point[i][j] + 1, point[i + 1][j])
                elif j == arr[i + 1]:
                    point[i + 1][arr[i]] = min(point[i + 1][arr[i]], point[i][j] + 1)
                else:
                    point[i + 1][j] = min(point[i][j] + judge(arr[i], arr[i + 1]), point[i + 1][j])
                    point[i + 1][arr[i]] = min(point[i][j] + judge(j, arr[i + 1]), point[i + 1][arr[i]])
    print(min(point[-1]))
# 8 * 10 ** 5
# point[몇 번째][나머지 발]
# arr[몇 번째] = 눌러야 하는 곳
# arr[i], j