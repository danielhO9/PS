N = int(input())
switch = False
for i in range(5):
    if (N - 3 * i) >= 0 and (N - 3 * i) % 5 == 0:
        switch = True
        print((N - 3 * i) // 5 + i)
        break
if not switch:
    print(-1)