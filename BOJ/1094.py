import sys
input = sys.stdin.readline

X = int(input())
X_bin = bin(X)[2:]
answer = 0
for i in X_bin:
    if i == '1':
        answer += 1
print(answer)