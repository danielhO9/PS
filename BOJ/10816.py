import sys
input = sys.stdin.readline
import bisect

N = int(input())
n = list(map(int, input().split()))
M = int(input())
m = list(map(int, input().split()))
n.sort()
for i in m:
    print(bisect.bisect_right(n, i) - bisect.bisect_left(n, i), end = ' ')