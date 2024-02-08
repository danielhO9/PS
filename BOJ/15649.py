import sys
input = sys.stdin.readline

N, M = map(int, input().split())
ans = []
def solution():
    if len(ans) == M:
        for i in ans:
            print(i, end = ' ')
        print()
        return
    for i in range(1, N + 1):
        if i not in ans:
            ans.append(i)
            solution()
            ans.pop()
solution()