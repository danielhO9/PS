import sys
input = sys.stdin.readline

def meet(x1, y1, x2, y2, x3, y3, x4, y4):
    if y1 == y2 and y3 == y4:
        if y1 == y3:
            if max(x1, x2) < min(x3, x4):
                return False
            elif max(x3, x4) < min(x1, x2):
                return False
            elif max(x1, x2) == min(x3, x4):
                return True
            elif max(x3, x4) == min(x1, x2):
                return True
            else:
                return True
        else:
            return False
    elif y1 == y2:
        if min(y3, y4) <= y1 <= max(y3, y4):
            if y4 > y3:
                if min(x1, x2) * (y4 - y3) <= (x4 - x3) * (y1 - y3) + x3 * (y4 - y3) <= max(x1, x2) * (y4 - y3):
                    return True
                else:
                    return False
            else:
                if max(x1, x2) * (y4 - y3) <= (x4 - x3) * (y1 - y3) + x3 * (y4 - y3) <= min(x1, x2) * (y4 - y3):
                    return True
                else:
                    return False
        else:
            return False
    elif y3 == y4:
        if min(y1, y2) <= y3 <= max(y1, y2):
            if y2 > y1:
                if min(x3, x4) * (y2 - y1) <= (x2 - x1) * (y3 - y1) + x1 * (y2 - y1) <= max(x3, x4) * (y2 - y1):
                    return True
                else:
                    return False
            else:
                if max(x3, x4) * (y2 - y1) <= (x2 - x1) * (y3 - y1) + x1 * (y2 - y1) <= min(x3, x4) * (y2 - y1):
                    return True
                else:
                    return False
        else:
            return False
    else:
        if (x2 - x1) * (y4 - y3) == (x4 - x3) * (y2 - y1):
            if (y4 - y3) * (y2 - y1) * (x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) == 0:
                if max(y1, y2) < min(y3, y4):
                    return False
                elif max(y3, y4) < min(y1, y2):
                    return False
                elif max(y1, y2) == min(y3, y4):
                    if max(x1, x2) == min(x3, x4):
                        return True
                    else:
                        return True
                elif max(y3, y4) == min(y1, y2):
                    if max(x1, x2) == min(x3, x4):
                        return True
                    else:
                        return True
                else:
                    return True
            else:
                return False
        else:
            if (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1) > 0:
                if min(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (
                        x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= max(y1, y2) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) and min(y3, y4) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (
                        x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= max(y3, y4) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)):
                    return True
                else:
                    return False
            else:
                if max(y1, y2) * ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (
                        x3 - x1) + (x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= min(y1, y2) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) and max(y3, y4) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)) <= (y4 - y3) * (y2 - y1) * (x3 - x1) + (
                        x2 - x1) * y1 * (y4 - y3) - (x4 - x3) * y3 * (y2 - y1) <= min(y3, y4) * (
                        (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1)):
                    return True
                else:
                    return False

N = int(input())
parents = []
for i in range(N):
    parents.append(i)

def find(x):
    if parents[x] == x:
        return parents[x]
    return find(parents[x])

def union(a, b):
    a = find(a)
    b = find(b)
    parents[a], parents[b] = min(a, b), min(a, b)

spots = []
# 최대 3000개, 450만번 연산
for i in range(N):
    spot = list(map(int, input().split()))
    for each in range(len(spots)):
        if meet(spots[each][0], spots[each][1], spots[each][2], spots[each][3], spot[0], spot[1], spot[2], spot[3]):
            union(each, i)
    spots.append(spot)
# print(parents)
visited = [0] * N
for i in range(len(parents)):
    visited[find(i)] += 1
cnt = 0
for i in visited:
    if i != 0:
        cnt += 1
print(cnt)
print(max(visited))