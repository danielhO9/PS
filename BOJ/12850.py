# 행렬곱 구현
def multiplication(a, b):
    answer = []
    for i in range(len(a)):
        answer.append([])
        for j in range(len(b[0])):
            temp_answer = 0
            for k in range(len(a[i])):
                temp_answer += a[i][k] * b[k][j]
            answer[-1].append(temp_answer % 1000000007)
    return answer
D = int(input())
x = [
    [0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 1, 0, 0, 0, 0],
    [1, 1, 0, 1, 1, 0, 0, 0],
    [0, 1, 1, 0, 1, 1, 0, 0],
    [0, 0, 1, 1, 0, 1, 1, 0],
    [0, 0, 0, 1, 1, 0, 0, 1],
    [0, 0, 0, 0, 1, 0, 0, 1],
    [0, 0, 0, 0, 0, 1, 1, 0]
]
def solution(D):
    if D == 1:
        return x
    half = solution(D // 2)
    if D % 2 == 1:
        return multiplication(multiplication(half, half), x)
    return multiplication(half, half)
print(multiplication(solution(D), [[1], [0], [0], [0], [0], [0], [0], [0]])[0][0] % 1000000007)