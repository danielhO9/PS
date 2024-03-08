import sys
input = sys.stdin.readline

x1, y1, x2, y2 = map(int, input().split())
x3, y3, x4, y4 = map(int, input().split())

if y1 == y2 and y3 == y4:
    if y1 == y3:
        if max(x1, x2) < min(x3, x4):
            print(0)
        elif max(x3, x4) < min(x1, x2):
            print(0)
        elif max(x1, x2) == min(x3, x4):
            print(1)
            # print(max(x1, x2), y1)
        elif max(x3, x4) == min(x1, x2):
            print(1)
            # print(max(x3, x4), y1)
        else:
            print(1)
    else:
        print(0)
elif y1 == y2:
    if min(y3, y4) <= y1 <= max(y3, y4):
        if y4 > y3:
            if min(x1, x2) * (y4 - y3) <= (x4 - x3) * (y1 - y3) + x3 * (y4 - y3) <= max(x1, x2) * (y4 - y3):
                print(1)
                # print(((x4 - x3) * (y1 - y3) + x3 * (y4 - y3)) / (y4 - y3), y1)
            else:
                print(0)
        else:
            if max(x1, x2) * (y4 - y3) <= (x4 - x3) * (y1 - y3) + x3 * (y4 - y3) <= min(x1, x2) * (y4 - y3):
                print(1)
                # print(((x4 - x3) * (y1 - y3) + x3 * (y4 - y3)) / (y4 - y3), y1)
            else:
                print(0)
    else:
        print(0)
elif y3 == y4:
    if min(y1, y2) <= y3 <= max(y1, y2):
        if y2 > y1:
            if min(x3, x4) * (y2 - y1) <= (x2 - x1) * (y3 - y1) + x1 * (y2 - y1) <= max(x3, x4) * (y2 - y1):
                print(1)
                # print(((x2 - x1) * (y3 - y1) + x1 * (y2 - y1)) / (y2 - y1), y3)
            else:
                print(0)
        else:
            if max(x3, x4) * (y2 - y1) <= (x2 - x1) * (y3 - y1) + x1 * (y2 - y1) <= min(x3, x4) * (y2 - y1):
                print(1)
                # print(((x2 - x1) * (y3 - y1) + x1 * (y2 - y1)) / (y2 - y1), y3)
            else:
                print(0)
    else:
        print(0)
else:
    if (x2 - x1) * (y4 - y3) == (x4 - x3) * (y2 - y1):
        if (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) == 0:
            if max(y1, y2) < min(y3, y4):
                print(0)
            elif max(y3, y4) < min(y1, y2):
                print(0)
            elif max(y1, y2) == min(y3, y4):
                if max(x1, x2) == min(x3, x4):
                    print(1)
                    # print(max(x1, x2), max(y1, y2))
                else:
                    print(1)
                    # print(max(x3, x4), max(y1, y2))
            elif max(y3, y4) == min(y1, y2):
                if max(x1, x2) == min(x3, x4):
                    print(1)
                    # print(max(x1, x2), max(y3, y4))
                else:
                    print(1)
                    # print(max(x3, x4), max(y3, y4))
            else:
                print(1)
        else:
            print(0)
    else:
        if (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1) > 0:
            if min(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= max(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) and min(y3, y4) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= max(y3, y4) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)):
                print(1)
                # print(((x2 - x1) * ((y4 - y3) * (x3 - x1) + (x4 - x3) * (y1 - y3)) + ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) * x1) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)), ((y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1)) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)))
            else:
                print(0)
        else:
            if max(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= min(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) and max(y3, y4) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= min(y3, y4) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)):
                print(1)
                # print(((x2 - x1) * ((y4 - y3) * (x3 - x1) + (x4 - x3) * (y1 - y3)) + ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) * x1) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)), ((y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1)) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)))
            else:
                print(0)
