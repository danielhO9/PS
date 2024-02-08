import sys
input = sys.stdin.readline

G = int(input())
P = int(input())
g = []
for i in range(P):
    g.append(int(input()))
parent = {}
for i in range(1, G + 1):
    parent[i] = i
def find_parent(x):
    if parent[x] == x:
        return x
    parent[x] = find_parent(parent[x])
    return parent[x]

def union(a, b):
    parent_a, parent_b = find_parent(a), find_parent(b)
    if parent_a != parent_b:
        parent[parent_a], parent[parent_b] = min(parent_a, parent_b), min(parent_a, parent_b)
switch = True
answer = 0
for i in g:
    parent_i = find_parent(i)
    if parent_i == 1:
        if switch:
            answer += 1
            switch = False
        else:
            break
    else:
        answer += 1
        union(parent_i, parent_i - 1)
print(answer)