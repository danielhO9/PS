import sys
input = sys.stdin.readline
sys.setrecursionlimit(10 ** 5)

n, m = map(int, input().split())
parent = {}
for i in range(n + 1):
    parent[i] = i

def find_parent(x):
    if x == parent[x]:
        return x
    parent[x] = find_parent(parent[x])
    return parent[x]

def union(a, b):
    parent_a = find_parent(a)
    parent_b = find_parent(b)
    if parent_a != parent_b:
        parent[parent_a], parent[parent_b] = min(parent_a, parent_b), min(parent_a, parent_b)

for i in range(m):
    how, a, b = map(int, input().split())
    if how == 0:
        union(a, b)
    else:
        if find_parent(a) == find_parent(b):
            print("YES")
        else:
            print("NO")
