import sys
input = sys.stdin.readline

N = int(input())
n = list(map(int, input().split()))
M = int(input())
n.sort()
def find(target):
    value = 0
    for i in n:
        value += min(target, i)
    return value

def binary_search():
    start, end = 0, n[-1]
    while start <= end:
        mid = start + (end - start) // 2
        value = find(mid)
        if value == M:
            return mid
        elif value < M:
            start = mid + 1
            if find(mid + 1) > M or mid == n[-1]:
                return mid
        else:
            end = mid - 1
print(binary_search())