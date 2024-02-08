import sys
input = sys.stdin.readline

N = int(input())
arr = []
for i in range(N):
    do = input().strip()
    if do == "pop":
        if not arr:
            print(-1)
        else:
            print(arr.pop())
    elif do == "size":
        print(len(arr))
    elif do == "empty":
        if arr:
            print(0)
        else:
            print(1)
    elif do == "top":
        if not arr:
            print(-1)
        else:
            print(arr[-1])
    else:
        push = list(do.split())
        arr.append(int(push[1]))
