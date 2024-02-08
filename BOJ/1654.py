import sys
input = sys.stdin.readline

N, K = map(int, input().split())
n = []
for i in range(N):
    n.append(int(input()))
n.sort()
def find(lenght):
    value = 0
    for i in n:
        value += i // lenght
    return value

def binary_search():
    start, end = 1, n[-1]
    while start <= end:
        mid = start + (end - start) // 2
        value = find(mid)
        if value >= K:
            start = mid + 1
            if find(mid + 1) < K:
                return mid
        else:
            end = mid - 1
            if find(mid - 1) >= K:
                return mid - 1
print(binary_search())