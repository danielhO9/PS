import sys
input = sys.stdin.readline
print = sys.stdout.write

def solution(product, graph):
    # dp[i]는 i개의 product에 대한 최소 비용
    # dp[i] = min(0.5 * product[j][1] * product[i - 1][0] + dp[j] + 0.25 * product[j][1] ** 2) + 0.25 * product[i - 1][0] ** 2
    # dp = [0]
    x = 0
    graph.clear()
    index = 0
    for count in range(1, len(product) + 1):
        slope, y_value = 2 * product[count - 1][1], x + product[count - 1][1] ** 2
        # graph 최신화
        while graph and graph[-1][2] >= meetPoint(graph[-1], (slope, y_value)):
            if index == len(graph) - 1:
                index -= 1
            graph.pop()
        if graph:
            graph.append((slope, y_value, meetPoint(graph[-1], (slope, y_value))))
        else:
            graph.append((slope, y_value, 10 ** 8 * (-1)))
        # index 최신화
        while index != len(graph) - 1 and graph[index + 1][2] <= product[count - 1][0]:
            index += 1
        # 이분탐색
        # start, end = 0, len(graph) - 1
        # while start <= end:
        #     mid = (start + end) // 2
        #     if graph[mid][2] <= product[count - 1][0]:
        #         if mid == end or graph[mid + 1][2] >= product[count - 1][0]:
        #             index = mid
        #             break
        #         else:
        #             start = mid + 1
        #     else:
        #         end = mid - 1
        # while index > 0:
        #     index -= 1
        #     graph.popleft()

        # dp 최신화
        x = graph[index][0] * product[count - 1][0] + graph[index][1] + product[count - 1][0] ** 2
        if count == len(product):
            print(f'{x // 4}.' + ['00','25','50','75'][x % 4] + '\n')
def meetPoint(line1, line2): return (line2[1] - line1[1]) / (line1[0] - line2[0])

for _ in range(int(input())):
    # arr로 input 받음
    arr1 = [list(map(int, input().split())) for _ in range(int(input()))]
    arr2 = [[each[1] - each[0], each[0] + each[1]] for each in arr1]
    arr2.sort()

    # product로 정제
    product = []
    for i in arr2:
        while product and product[-1][1] <= i[1]:
            product.pop()
        product.append(i)

    graph = []
    solution(product, graph)
