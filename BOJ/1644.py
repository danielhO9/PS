import sys
input = sys.stdin.readline

N = int(input())
arr = [True] * (N + 1)
prime = []
arr[0], arr[1] = False, False
for i in range(len(arr)):
    if arr[i] == True:
        prime.append(i)
        value = i
        while value <= N:
            arr[value] = False
            value += i
if N == 1:
    print(0)
else:
    start, end, value, answer = 0, 0, prime[0], 0
    while True:
        if value < N:
            end += 1
            if end == len(prime):
                break
            value += prime[end]
        elif value == N:
            answer += 1
            start += 1
            if start == len(prime):
                break
            end, value = start, prime[start]
        elif value > N:
            start += 1
            if start > end:
                break
            value -= prime[start - 1]
    print(answer)