import sys
input = sys.stdin.readline
import bisect

T = int(input())
n = int(input())
A = list(map(int, input().split()))
m = int(input())
B = list(map(int, input().split()))
answer = 0

def sumMachine(A):
    answer = []
    for i in range(len(A)):
        temp = 0
        for j in range(i, len(A)):
            temp += A[j]
            answer.append(temp)
    return answer
arr_A, arr_B = sumMachine(A), sumMachine(B)
arr_A.sort()
arr_B.sort()
for a in arr_A:
    answer += bisect.bisect_right(arr_B, T - a) - bisect.bisect_left(arr_B, T - a)
print(answer)