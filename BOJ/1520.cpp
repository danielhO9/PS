#include <bits/stdc++.h>
using namespace std;
int M, N, mapp[500][500], cache[500][500];

int matchCache(int y, int x) {
    if (y == M - 1 && x == N - 1) return 1;
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    ret = 0;
    if (y + 1 < M && mapp[y + 1][x] < mapp[y][x]) ret += matchCache(y + 1, x);
    if (y - 1 >= 0 && mapp[y - 1][x] < mapp[y][x]) ret += matchCache(y - 1, x);
    if (x + 1 < N && mapp[y][x + 1] < mapp[y][x]) ret += matchCache(y, x + 1);
    if (x - 1 >= 0 && mapp[y][x - 1] < mapp[y][x]) ret += matchCache(y, x - 1);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> M >> N;
    for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) cin >> mapp[i][j];
    memset(cache, -1, sizeof(cache));
    cout << matchCache(0, 0);
    return 0;
}