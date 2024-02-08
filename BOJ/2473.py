import sys
input = sys.stdin.readline

N = int(input())
n = list(map(int, input().split()))
n.sort()
def two_pointer(target):
    start, end = 0, len(n) - 1
    arr = [[n[0], n[-1]], abs(n[0] + n[-1] + target)]
    while start < end:
        if n[start] + n[end] + target == 0:
            return [n[start], n[end]]
        elif n[start] + n[end] + target > 0:
            if arr[1] > abs(n[start] + n[end] + target):
                arr = [[n[start], n[end]], abs(n[start] + n[end] + target)]
            end -= 1
        else:
            if arr[1] > abs(n[start] + n[end] + target):
                arr = [[n[start], n[end]], abs(n[start] + n[end] + target)]
            start += 1
    return arr[0]
ans = 1000000000 * 3
for i in range(N - 2):
    max_value = n[-1]
    n.pop()
    arr = two_pointer(max_value)
    if abs(arr[0] + arr[1] + max_value) < ans:
        ans_arr = [arr[0], arr[1], max_value]
        ans = abs(arr[0] + arr[1] + max_value)
for i in ans_arr:
    print(i, end = ' ')