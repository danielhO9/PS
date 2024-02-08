import sys
input = sys.stdin.readline

N = int(input())
n = list(map(int, input().split()))
M = int(input())
m = list(map(int, input().split()))
n.sort()
def binary_search(target):
    start, end = 0, N - 1
    while start <= end:
        mid = (end - start) // 2 + start
        if n[mid] == target:
            return 1
        elif n[mid] < target:
            start = mid + 1
        else:
            end = mid - 1
    return 0
for i in m:
    print(binary_search(i), end = ' ')