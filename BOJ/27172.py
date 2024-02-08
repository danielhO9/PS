import sys
input = sys.stdin.readline
import math

N = int(input())
X = list(map(int, input().split()))
inside = [False] * (1000001)
value = [0] * (1000001)
for i in X:
    inside[i] = True
def divisor(x):
    arr = []
    for i in range(1, math.floor(math.sqrt(x)) + 1):
        if x % i == 0:
            if i != int(x / i):
                arr.append(i)
                arr.append(int(x / i))
            else:
                arr.append(i)
    return arr
for i in X:
    arr = divisor(i)
    for j in arr:
        if inside[j] == True:
            value[i] -= 1
            value[j] += 1
for i in X:
    print(value[i], end = ' ')

# 각 숫자가 나오면 약수들을 계산한다. -> 1000번 연산
# 2000 * 100000 = 2 * 10 **8