import sys
input = sys.stdin.readline

N, C = map(int, input().split())
home = []
for i in range(N):
    home.append(int(input()))
home.sort()

def find(value):
    arr = []
    for i in range(len(home)):
        if i == 0:
            arr.append(home[i])
        if home[i] - arr[-1] >= value:
            arr.append(home[i])
    return len(arr)

def binary_search():
    start, end = 0, home[-1]
    while start <= end:
        mid = start + (end - start) // 2
        value = find(mid)
        if value >= C:
            start = mid + 1
            if find(mid + 1) < C:
                return mid
        else:
            end = mid - 1
print(binary_search())