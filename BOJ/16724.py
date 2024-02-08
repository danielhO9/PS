import sys
input = sys.stdin.readline

N, M = map(int, input().split())
parents = [i for i in range(N * M)]

def find(x):
    if x != parents[x]:
        parents[x] = find(parents[x])
    return parents[x]

answer = N * M
def union(a, b):
    global answer
    a, b = find(a), find(b)
    if a != b:
        answer -= 1
    parents[a], parents[b] = min(a, b), min(a, b)

for i in range(N):
    way = input().strip()
    for j in range(len(way)):
        if way[j] == "U":
            union(M * i + j, M * i + j - M)
        elif way[j] == "D":
            union(M * i + j, M * i + j + M)
        elif way[j] == "L":
            union(M * i + j, M * i + j - 1)
        elif way[j] == "R":
            union(M * i + j, M * i + j + 1)
print(answer)
