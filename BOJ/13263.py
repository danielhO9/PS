import sys
input = sys.stdin.readline

# 전기톱을 충전하는 비용은 완전히 자른 나무들 중 b_i의 최솟값이 된다.
# 완전히 잘려진 나무가 없다면 전기톱은 충전할 수 없고 사용할 수 없다.
# 만약 어떤 나무를 베기 시작했지만 그 나무를 안 베고 다른 나무를 베는 경우?
# 그런 경우는 있을 수 없다. 한 나무를 베기 시작했으면 끝을 봐야지
# 마지막 나무를 베면 더이상 나무를 베는 데에 충전 비용이 들지 않는다.
# 마지막 나무를 베기까지 번호를 거슬러가는 경우는 없다.

# dp(i) = min(dp(j) + b[j] * a[i])

n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
deque = [[b[0], 0, 0.0]]

def meetPoint(line1, line2):
    return (line2[1] - line1[1]) / (line1[0] - line2[0])

index = 0
for i in range(1, n):
    while index != len(deque) - 1 and deque[index + 1][2] < a[i]:
        index += 1
    while deque[-1][2] >= meetPoint(deque[-1], [b[i], deque[index][0] * a[i] + deque[index][1]]):
        if index == len(deque) - 1:
            index -= 1
        deque.pop()
    deque.append([b[i], deque[index][0] * a[i] + deque[index][1], meetPoint(deque[-1], [b[i], deque[index][0] * a[i] + deque[index][1]])])
    if i == n - 1:
        print(deque[index][0] * a[i] + deque[index][1])
if n == 1:
    print(0)
# 5 0
# 4 10
# 3 15
# 2 20
# 0 25
