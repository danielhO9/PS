import sys
import heapq
input = sys.stdin.readline

N, M = map(int, input().split())
have_to = [[] for i in range(N + 1)]
degree = [0] * (N + 1)
degree[0] = 1
arr = []
for i in range(M):
    before, after = map(int, input().split())
    have_to[before].append(after)
    degree[after] += 1
for i in range(len(degree)):
    if degree[i] == 0:
        heapq.heappush(arr, i)
while arr:
    now = arr[0]
    print(now, end = ' ')
    heapq.heappop(arr)
    for i in have_to[now]:
        degree[i] -= 1
        if degree[i] == 0:
            heapq.heappush(arr, i)


# 위상정렬
# 각 번호의 진입차수를 기록하는 배열을 만든다.

# 진입차수가 0인 문제 번호를 우선순위 큐에 담는다.
# 우선순위 큐의 최소 문제를 꺼낸다.
# 꺼낸 문제에서 출발하는 문제들의 진입차수를 1 줄인다.
# 위의 과정 반복