import sys
input = sys.stdin.readline

class UF:
    def __init__(self, n):
        self.par = list(range(n))
        self.rk = [0] * n

    def find(self, x):
        if self.par[x] != x:
            self.par[x] = self.find(self.par[x])
        return self.par[x]

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return
        if self.rk[x] > self.rk[y]:
            x, y = y, x
        self.par[x] = y
        if self.rk[x] == self.rk[y]:
            self.rk[y] += 1


def solve():
    k = int(input())
    length = list(map(int, input().split()))

    n = int(input())
    tokens = []
    while len(tokens) < 3:
        tokens += input().split()

    s0 = tokens[0]
    n  = int(tokens[1])
    s1 = tokens[2]

    m = {}
    cnt = 0

    m[('0', 0)] = cnt; cnt += 1
    m[('1', 0)] = cnt; cnt += 1

    v = [[], []]

    for idx, s in enumerate([s0, s1]):
        for c in s:

            if c == '0' or c == '1':
                v[idx].append(m[(c, 0)])

            else:
                L = length[ord(c) - ord('a')]
                for j in range(L):
                    key = (c, j)
                    if key not in m:
                        m[key] = cnt
                        cnt += 1
                    v[idx].append(m[key])
    
    if (len(v[0]) != len(v[1])):
        print(0)
        return

    uf = UF(cnt)

    for a, b in zip(v[0], v[1]):
        uf.merge(a, b)
    
    if (uf.find(0) == uf.find(1)):
        print(0)
        return

    ans = sum(1 for i in range(cnt) if uf.find(i) == i)
    ans -= 2
    if (ans < 0):
        print(0)
    else:
        print(2 ** ans)


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()
