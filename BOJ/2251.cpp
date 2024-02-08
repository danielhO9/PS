#include <bits/stdc++.h>
using namespace std;
int A, B, C;
bool cache[200][200][200];

void bfs(int a, int b, int c) {
    // b -> a
    if (!cache[min(A, a + b)][a + b - min(A, a + b)][c]) {
        cache[min(A, a + b)][a + b - min(A, a + b)][c] = 1;
        bfs(min(A, a + b), a + b - min(A, a + b), c);
    }
    if (!cache[a + b - min(B, a + b)][min(B, a + b)][c]) {
        cache[a + b - min(B, a + b)][min(B, a + b)][c] = 1;
        bfs(a + b - min(B, a + b), min(B, a + b), c);
    }
    if (!cache[a][b + c - min(C, b + c)][min(C, b + c)]) {
        cache[a][b + c - min(C, b + c)][min(C, b + c)] = 1;
        bfs(a, b + c - min(C, b + c), min(C, b + c));
    }
    if (!cache[a][min(B, b + c)][b + c - min(B, b + c)]) {
        cache[a][min(B, b + c)][b + c - min(B, b + c)] = 1;
        bfs(a, min(B, b + c), b + c - min(B, b + c));
    }
    if (!cache[a + c - min(C, a + c)][b][min(C, a + c)]) {
        cache[a + c - min(C, a + c)][b][min(C, a + c)] = 1;
        bfs(a + c - min(C, a + c), b, min(C, a + c));
    }
    if (!cache[min(A, a + c)][b][a + c - min(A, a + c)]) {
        cache[min(A, a + c)][b][a + c - min(A, a + c)] = 1;
        bfs(min(A, a + c), b, a + c - min(A, a + c));
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> A >> B >> C;
    cache[0][0][C] = 1;
    bfs(0, 0, C);
    for (int i = 0; i <= C; ++i) {
        if (cache[0][C - i][i]) cout << i << " ";
    }
}