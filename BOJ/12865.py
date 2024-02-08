import sys
input = sys.stdin.readline

N, K = map(int, input().split())
dict = {}
for i in range(N):
    exp = {}
    for j in range(K + 1):
        exp[j] = 0
    dict[i + 1] = exp

for i in range(1, N + 1):
    weight, value = map(int, input().split())
    if i == 1:
        for j in range(1, K + 1):
            if j >= weight:
                dict[i][j] = value
    else:
        for j in range(1, K + 1):
            if j >= weight:
                dict[i][j] = max(dict[i - 1][j], dict[i - 1][j - weight] + value)
            else:
                dict[i][j] = dict[i - 1][j]
print(dict[N][K])


# 재귀함수를 이용한 풀이의 시간 복잡도 : 2^100 약 10^30
# 물품 개수에 따라 무게 1부터 K까지 모두 만든다 : 10^7
# Fn(K) = max(Fn-1(K), Fn-1(K-wn) + vn)
# n번째일때 확인하려면 wn이 K보다 작아야 한다.
# n-1개의 물품일 때의 값들이 모두 필요함.
# dict[물품 번호][무게에 따른 최대 가치]
