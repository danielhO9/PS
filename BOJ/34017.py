import sys
input = sys.stdin.readline

def f(n):
    if n == 1:
        return 1
    if n == 2:
        return 3
    if n == 3:
        return 10
    if n == 4:
        return 23
    rem = n % 3
    m = n // 3
    if rem == 0:
        return 2 * f(m + 1) + 2 * (m - 1) + 4
    if rem == 1:
        return 2 * f(m + 2) + 2 * (m - 1) + 3
    if rem == 2:
        return 2 * f(m) + 2 * m + 3
    
    return 0

Q = int(input())

for i in range(Q):
    N = int(input())
    print(f(N))