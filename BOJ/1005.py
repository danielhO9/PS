T = int(input())
def solution():
    N, K = map(int, input().split())
    D = list(map(int, input().split()))
    flow = []
    for i in range(N + 1):
        flow.append([])
    for i in range(K):
        rule = list(map(int, input().split()))
        flow[rule[1]].append(rule[0])

    question = int(input())
    arr = [-1] * (N + 1)
    for i in range(1, len(flow)):
        if len(flow[i]) == 0:
            arr[i] = D[i - 1]
    while arr[question] == -1:
        for i in range(1, len(flow)):
            if arr[i] == -1:
                switch = True
                ans = []
                for j in flow[i]:
                    if arr[j] == -1:
                        switch = False
                        break
                    ans.append(arr[j])
                if switch:
                    arr[i] = D[i - 1] + max(ans)
    return arr[question]
answer = []
for i in range(T):
    value = solution()
    answer.append(value)
for i in answer:
    print(i)