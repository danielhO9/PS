import sys
input = sys.stdin.readline

def solution():
    V, E = map(int, input().split())
    edges = []
    for i in range(E):
        edge = list(map(int, input().split()))
        edges.append(edge)
    edges.sort(key=lambda x: x[2])

    if V == 1:
        return 0

    answer = edges[0][2]
    vertex = [0] * (V + 1)
    count = 1
    vertex[edges[0][0]], vertex[edges[0][1]] = 1, 1
    for edge in edges:
        if vertex[edge[0]] == 0 and vertex[edge[1]] == 0:
            count += 1
            vertex[edge[0]], vertex[edge[1]] = count, count
            answer += edge[2]
        elif vertex[edge[0]] != 0 and vertex[edge[1]] != 0:
            if vertex[edge[0]] != vertex[edge[1]]:
                value = vertex[edge[1]]
                for i in range(1, len(vertex)):
                    if vertex[i] == value:
                        vertex[i] = vertex[edge[0]]
                answer += edge[2]
        else:
            sum = vertex[edge[0]] + vertex[edge[1]]
            vertex[edge[0]], vertex[edge[1]] = sum, sum
            answer += edge[2]
    return answer
print(solution())