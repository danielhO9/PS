import sys
input = sys.stdin.readline

T = int(input())
for i in range(T):
    string = input().strip()
    arr = []
    switch = True
    for j in string:
        if j == "(":
            arr.append(j)
        else:
            if arr:
                arr.pop()
            else:
                switch = False
                break
    if switch and len(arr) == 0:
        print("YES")
    else:
        print("NO")