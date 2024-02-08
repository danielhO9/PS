import sys
input = sys.stdin.readline

# N은 거리에 있는 아이들의 수, M은 아이들의 친구 관계 수, K는 공명하기 위한 최소 아이 수
N, M, K = map(int, input().split())
candies = list(map(int, input().split()))

parents = [i for i in range(N)]
def find(x):
    if x != parents[x]:
        parents[x] = find(parents[x])
    return parents[x]
def union(a, b):
    a, b = find(a), find(b)
    parents[a], parents[b] = min(a, b), min(a, b)

for _ in range(M):
    a, b = map(int, input().split())
    union(a - 1, b - 1)

kids = [0] * N
group_candies = [0] * N
group_index = set([])
for i in range(N):
    index = find(i)
    kids[index] += 1
    group_candies[index] += candies[i]
    group_index.add(index)
group_index = list(group_index)
# print(kids)
# print(group_candies)
dp = []
temp = []
for i in range(K):
    if i >= kids[group_index[0]]:
        temp.append(group_candies[group_index[0]])
    else:
        temp.append(0)
dp.append(temp)

for i in range(1, len(group_index)):
    temp = []
    for j in range(K):
        if j >= kids[group_index[i]]:
            temp.append(max(dp[-1][j], dp[-1][j - kids[group_index[i]]] + group_candies[group_index[i]]))
        else:
            temp.append(dp[-1][j])
    dp.append(temp)
print(dp[-1][-1])