import sys
input = sys.stdin.readline

N, S = map(int, input().split())
arr = list(map(int, input().split()))
start, end, sum, ans = 0, 0, arr[0], N + 1
while end < N:
    if sum < S:
        end += 1
        if end == N:
            break
        sum += arr[end]
    elif sum >= S:
        ans = min(ans, end - start + 1)
        if start == end:
            start += 1
            end += 1
            if end == N:
                break
            sum = arr[start]
        else:
            sum -= arr[start]
            start += 1
if ans == N + 1:
    print(0)
else:
    print(ans)
