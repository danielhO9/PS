import sys
input = sys.stdin.readline

N = int(input())
k = int(input())

def find(target):
    value_min, value_max = 0, 0
    for i in range(1, min(N + 1, target + 1)):
        if target % i == 0 and i * N >= target:
            value_min += min(target // i - 1, N)
            value_max += min(target // i, N)
        else:
            value_min += min(target // i, N)
            value_max += min(target // i, N)
    return [value_min, value_max]

def binary_search():
    start, end = 1, N * N
    while start <= end:
        mid = start + (end - start) // 2
        arr = find(mid)
        if arr[0] < k <= arr[1]:
            return mid
        elif k <= arr[0]:
            end = mid - 1
        elif arr[1] < k:
            start = mid + 1
print(binary_search())