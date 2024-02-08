N, K = map(int, input().split())

arr = [True] * (N + 1)
arr[0], arr[1] = False, False
count = 0
answer = 0
while count < K:
    for i in range(len(arr)):
        if arr[i] == True:
            for j in range(i, len(arr)):
                if j % i == 0 and arr[j] == True:
                    count += 1
                    answer = j
                    arr[j] = False
                    if count == K:
                        break
            break
print(answer)