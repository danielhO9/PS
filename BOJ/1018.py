import sys
input = sys.stdin.readline

N, M = map(int, input().split())
arr = []
for i in range(N):
    arr.append(input().strip())
def check(y, x):
    a, b = 0, 0
    for i in range(y, y + 8):
        for j in range(x, x + 8):
            if (i + j) % 2 == 0:
                if arr[i][j] == 'W':
                    a += 1
                else:
                    b += 1
            else:
                if arr[i][j] == 'W':
                    b += 1
                else:
                    a += 1
    return min(a, b)
ans = 2500
for i in range(0, N - 7):
    for j in range(0, M - 7):
        ans = min(ans, check(i, j))
print(ans)