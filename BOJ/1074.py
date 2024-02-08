import sys
input = sys.stdin.readline

ans = 0
N, r, c = map(int, input().split())
for i in range(N - 1, -1, -1):
    a, b = 1 << i | r == r, 1 << i | c == c
    if a and b:
        ans += 2 ** (2 * i) * 3
    elif a:
        ans += 2 ** (2 * i) * 2
    elif b:
        ans += 2 ** (2 * i)
print(ans)

# 3, 4, 5
# 0b100, 0b101