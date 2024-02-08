import sys
input = sys.stdin.readline
from collections import deque

# dp[x][y] = max(dp[x - 1][i] - Si ** 2 + Si * Sy)
n, k = map(int, input().split())
arr = list(map(int, input().split()))
S = [0]
for i in arr:
    S.append(S[-1] + i)

def meetPoint(line1, line2):
    if S[line1[0]] - S[line2[0]] == 0:
        return line1[2]
    return (line2[1] - line1[1]) / (S[line1[0]] - S[line2[0]])

dp = [0] * n
graph = deque([])
index_list = [[]]

for slice in range(k):
    index = 0
    for lenght in range(slice + 1, n):
        while graph and graph[-1][2] >= meetPoint(graph[-1], [lenght, dp[lenght - slice - 1] - S[lenght] ** 2]):
            if index == len(graph) - 1:
                index -= 1
            graph.pop()
        if len(graph) == 0:
            graph.append([lenght, dp[lenght - slice - 1] - S[lenght] ** 2, 0])
            # print("inserted graph:",graph[-1])
        else:
            graph.append([lenght, dp[lenght - slice - 1] - S[lenght] ** 2, meetPoint(graph[-1], [lenght, dp[lenght - slice - 1] - S[lenght] ** 2])])
            # print("inserted graph:",graph[-1])
        while index != len(graph) - 1 and graph[index + 1][2] <= S[lenght + 1]:
            index += 1
        while index > 0:
            graph.popleft()
            index -= 1
        # print("chosen graph:",graph[index])
        index_list[-1].append(graph[index][0])
        dp[lenght - slice - 1] = S[graph[index][0]] * S[lenght + 1] + graph[index][1]
        # print(S[lenght + 1], dp[lenght - slice - 1])
    dp.pop()
    graph = deque([])
    if slice != k - 1:
        index_list.append([])
    else:
        print(dp[-1])
answer = [index_list[-1][-1]]
for i in range(k - 1, 0, -1):
    answer.append(index_list[i - 1][answer[-1] - i - 1])
for i in range(k):
    print(answer[k - 1 - i], end = " ")
