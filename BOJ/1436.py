N = int(input())
number = 1
count = 0
while count < N:
    number += 1
    string = str(number)
    if '666' in string:
        count += 1
print(number)