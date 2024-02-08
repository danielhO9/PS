N = int(input())
arr = []
for i in range(N):
    string = input()
    arr.append([len(string), string])
arr.sort()
string = ''
for i in arr:
    if string == i[1]:
        continue
    string = i[1]
    print(i[1])