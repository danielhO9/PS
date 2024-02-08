import sys
input = sys.stdin.readline
import bisect

# 철수는 카드를 버리고 다시 들고오거나 민수한테 없는 카드를 내기도 한다.
# 철수 -> 1부터 N 중 무엇이든 가능
# 민수는 철수가 낼 카드보다 큰 카드가 있다면 그 카드들 중 가장 작은 카드를 낸다.

N, M, K = map(int, input().split())
submit = list(map(int, input().split()))
get = list(map(int, input().split()))
submit.sort()

# 문제는 이미 낸 카드를 관리할 줄 알아야 한다. 이 과정에서 이분탐색을 사용하자.
parents = [i for i in range(M)]

def find(x):
    if x != parents[x]:
        parents[x] = find(parents[x])
    return parents[x]

def union(a, b):
    a, b = find(a), find(b)
    parents[a], parents[b] = max(a, b), max(a, b)

# 이미 낸 카드는 parents를 바로 다음 값과 합친다.
for chelsoo in get:
    index = bisect.bisect_right(submit, chelsoo)
    print(submit[find(index)])
    if find(index) != M - 1:
        union(find(index), find(index) + 1)