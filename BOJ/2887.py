import sys
input = sys.stdin.readline
import heapq

# x, y, z를 기준으로 생각하면 됨
# 모든 경우를 따질 필요 없다

N = int(input())
planets = []
for i in range(N):
    planets.append(list(map(int, input().split())))
    planets[-1].append(i)

graph = []
for i in range(3):
    sorted_planets = sorted(planets, key=lambda x : x[i])
    for j in range(len(sorted_planets) - 1):
        heapq.heappush(graph, [sorted_planets[j + 1][i] - sorted_planets[j][i], sorted_planets[j + 1][3], sorted_planets[j][3]])

parents = [i for i in range(N)]
def find(x):
    if x != parents[x]:
        parents[x] = find(parents[x])
    return parents[x]

def union(a, b):
    a, b = find(a), find(b)
    parents[a], parents[b] = min(a, b), min(a, b)

cnt = 0
answer = 0
while cnt < N - 1:
    now = heapq.heappop(graph)
    if find(now[1]) != find(now[2]):
        answer += now[0]
        cnt += 1
        union(now[1], now[2])
print(answer)
