import sys
input = sys.stdin.readline

string = list(input())
string.pop()
arr = []
for i in range(len(string)):
    arr.append([-1] * (len(string) - i))
for i in range(len(string)):
    arr[i][0] = True
    if i < len(string) - 1:
        if string[i] == string[i + 1]:
            arr[i][1] = True
        else:
            arr[i][1] = False
def find(i, j):
    if arr[i][j] == -1:
        if string[i] != string[i + j]:
            arr[i][j] = False
        else:
            if arr[i + 1][j - 2] != -1:
                arr[i][j] = arr[i + 1][j - 2]
            else:
                find(i + 1, j - 2)
                arr[i][j] = arr[i + 1][j - 2]
for i in range(len(string)):
    for j in range(0, i + 1):
        find(j, i - j)

answer = [0] * len(string)
for i in range(len(string)):
    possible = []
    for j in range(0, i + 1):
        switch = False
        if j == 0 and arr[j][i - j] == True:
            switch = True
            break
        elif arr[j][i - j] == True:
            possible.append(answer[j - 1] + 1)
    if switch:
        answer[i] = 1
    else:
        answer[i] = min(possible)
print(answer[-1])