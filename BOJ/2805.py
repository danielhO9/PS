import sys
input = sys.stdin.readline

N, M = map(int, input().split())
trees = list(map(int, input().split()))
trees.sort()

def find(lenght):
    value = 0
    for i in trees:
        value += max(i - lenght, 0)
    return value

def binary_search(target):
    start, end = 0, trees[-1]
    while start <= end:
        mid = (end - start) // 2 + start
        value = find(mid)
        if value == M:
            return mid
        elif value < M:
            end = mid - 1
            if find(mid - 1) >= M:
                return mid - 1
        else:
            start = mid + 1
            if find(mid + 1) < M:
                return mid
print(binary_search(M))


