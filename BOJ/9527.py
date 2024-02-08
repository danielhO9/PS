import sys
input = sys.stdin.readline
import math

A, B = map(int, input().split())

def cnt(value):
    ans = 0
    value_copy = value
    log = math.floor(math.log2(value))
    for i in range(log, -1, -1):
        ans += 2 ** i * (value >> (i + 1))
        value_copy &= ~(1 << i)
        if value == value | 1 << i:
            ans += value_copy + 1
    return ans
if A == 1 and B == 1:
    print(1)
elif A == 1:
    print(cnt(B))
else:
    print(cnt(B) - cnt(A - 1))