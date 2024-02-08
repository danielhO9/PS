string = []
while True:
    trash = input()
    if len(trash) == 1:
        break
    string.append(trash)
for i in string:
    arr = []
    switch = True
    for j in i:
        if j == "(" or j == "[":
            arr.append(j)
        elif j == ")":
            if arr and arr[-1] == "(":
                arr.pop()
            else:
                switch = False
                break
        elif j == "]":
            if arr and arr[-1] == "[":
                arr.pop()
            else:
                switch = False
                break
    if switch and len(arr) == 0:
        print("yes")
    else:
        print("no")