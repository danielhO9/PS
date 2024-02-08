import sys
input = sys.stdin.readline
import heapq

N, K = map(int, input().split())
gemstones, bag = [], []
for i in range(N):
    each = list(map(int, input().split()))
    gemstones.append(each)
for i in range(K):
    limit = int(input())
    bag.append(limit)
gemstones.sort(reverse = True)
bag.sort()
now = []
heapq.heapify(now)
answer = 0
for limit in bag:
    while len(gemstones) > 0 and gemstones[-1][0] <= limit:
        value = gemstones.pop()
        value[0], value[1] = -value[1], value[0]
        heapq.heappush(now, value)
    if len(now) > 0:
        bring = heapq.heappop(now)
        answer += -bring[0]
print(answer)