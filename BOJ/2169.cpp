#include <bits/stdc++.h>
using namespace std;
int N, M, value[1000][1000], cache[3][1000][1000];

int dp(int id, int y, int x) {
    if (y == N - 1 && x == M - 1) return value[y][x];
    int& ret = cache[id][y][x];
    if (ret != -1e8 - 1) return ret;
    if (x - 1 >= 0 && y != N - 1 && id != 2) ret = max(ret, dp(1, y, x - 1) + value[y][x]);
    if (x + 1 < M && id != 1) ret = max(ret, dp(2, y, x + 1) + value[y][x]);
    if (y != N - 1) ret = max(ret, dp(0, y + 1, x) + value[y][x]);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> value[i][j];
    for (int i = 0; i < 3; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < M; ++k) cache[i][j][k] = -1e8 - 1;
    cout << dp(0, 0, 0);
    return 0;
}