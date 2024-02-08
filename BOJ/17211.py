import sys
input = sys.stdin.readline

N, condition = map(int, input().split())
a, b, c, d = map(float, input().split())
x = a - c
answer = x ** N * (1 - condition)
for i in range(N):
    answer += c * (x ** i)
print(round(answer * 1000))
print(round((1 - answer) * 1000))