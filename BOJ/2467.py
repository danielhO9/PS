import sys
input = sys.stdin.readline

N = int(input())
n = list(map(int, input().split()))
def binary_search(target):
    start, end = 0, len(n) - 1
    arr = [[n[0], n[-1]], abs(n[0] + n[-1])]
    while start < end:
        if n[start] + n[end] == target:
            return [n[start], n[end]]
        elif n[start] + n[end] > target:
            if arr[1] > abs(n[start] + n[end]):
                arr = [[n[start], n[end]], abs(n[start] + n[end])]
            end -= 1
        else:
            if arr[1] > abs(n[start] + n[end]):
                arr = [[n[start], n[end]], abs(n[start] + n[end])]
            start += 1
    return arr[0]
arr = binary_search(0)
for i in arr:
    print(i, end = ' ')