import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    arr.append(list(map(int, input().split())))
arr.sort()
for i in arr:
    print(i[0], i[1])