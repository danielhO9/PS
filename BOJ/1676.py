two, five = 0, 0
N = int(input())
if N != 0:
    for i in range(1, N + 1):
        if i % 2 == 0:
            value = 1
            while True:
                value += 1
                if i % (2 ** value) != 0:
                    break
            two += value - 1
        if i % 5 == 0:
            value = 1
            while True:
                value += 1
                if i % (5 ** value) != 0:
                    break
            five += value - 1
    print(min(two, five))
else:
    print(0)