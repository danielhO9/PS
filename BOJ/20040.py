import sys
input = sys.stdin.readline

n, m = map(int, input().split())
parents = []
for i in range(n):
    parents.append(i)

def find_parent(x):
    if parents[x] == x:
        return parents[x]
    return find_parent(parents[x])

def union_parent(a, b):
    a = find_parent(a)
    b = find_parent(b)
    parents[a], parents[b] = min(a, b), min(a, b)

def solution():
    for i in range(m):
        a, b = map(int, input().split())
        if find_parent(a) == find_parent(b):
            return i + 1
        union_parent(a, b)
    return 0
print(solution())