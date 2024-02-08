from collections import deque

N, K = map(int, input().split())
arr = deque([])
for i in range(1, N + 1):
    arr.append(i)
cnt = 0
print('<', end = '')
while arr:
    value = arr.popleft()
    cnt += 1
    if cnt % K == 0:
        print(value, end = '')
        if len(arr) != 0:
            print(',', end = ' ')
    else:
        arr.append(value)
print('>')
