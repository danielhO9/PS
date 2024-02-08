import sys
input = sys.stdin.readline

A, B, C = map(int, input().split())
answer = A % C
arr = [A % C]
for i in range(30):
    arr.append((arr[-1] ** 2) % C)
for i in range(31):
    if B - 1 == (B - 1) | 1 << i:
        answer *= arr[i]
        answer %= C
print(answer)

# 2 ** 31 - 1까지.
# A ** (2 ** 0), A ** (2 ** 1), A ** (2 ** 2), A ** (2 ** 3) ... A ** (2 ** 30)
# 이진법을 이용