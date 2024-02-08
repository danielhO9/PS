import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    age, name = input().split()
    arr.append([int(age), i, name])
arr.sort()
for i in arr:
    print(i[0], i[2])