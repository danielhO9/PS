import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    value = list(map(int, input().split()))
    arr.append([value[1], value[0]])
arr.sort()
for i in arr:
    print(i[1], i[0])