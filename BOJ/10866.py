import sys
input = sys.stdin.readline
from collections import deque

N = int(input())
arr = deque([])
for i in range(N):
    do = input().strip()
    if do == "pop_front":
        if not arr:
            print(-1)
        else:
            print(deque.popleft(arr))
    elif do == "pop_back":
        if not arr:
            print(-1)
        else:
            print(deque.pop(arr))
    elif do == "size":
        print(len(arr))
    elif do == "empty":
        if arr:
            print(0)
        else:
            print(1)
    elif do == "front":
        if not arr:
            print(-1)
        else:
            print(arr[0])
    elif do == "back":
        if not arr:
            print(-1)
        else:
            print(arr[-1])
    else:
        push = list(do.split())
        if push[0] == "push_front":
            arr.appendleft(int(push[1]))
        else:
            arr.append(int(push[1]))
