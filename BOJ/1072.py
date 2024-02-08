import sys
input = sys.stdin.readline
import math

X, Y = map(int, input().split())

def calculator(X, Y):
    return int(math.floor(100 * Y / X))

Z = calculator(X, Y)

def solution():
    if Z >= 99:
        return -1

    def binary_search():
        start, end = 0, X * X
        while start <= end:
            mid = start + (end - start) // 2
            value = calculator(X + mid, Y + mid)
            if value > Z:
                if calculator(X + mid - 1, Y + mid - 1) == Z:
                    return mid
                end = mid - 1
            elif value == Z:
                start = mid + 1

    answer = binary_search()
    return answer
print(solution())