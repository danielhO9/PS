#include <bits/stdc++.h>
using namespace std;
int n, bamboo[500][500], cache[500][500];
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, -1, 0, 1};

int matchCache(int y, int x) {
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    ret = 1;
    for (int i = 0; i < 4; ++i) {
        if (
            0 <= y + dy[i] &&
            0 <= x + dx[i] &&
            y + dy[i] < n &&
            x + dx[i] < n &&
            bamboo[y][x] < bamboo[y + dy[i]][x + dx[i]]
        ) ret = max(ret, matchCache(y + dy[i], x + dx[i]) + 1);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> bamboo[i][j];
    memset(cache, -1, sizeof(cache));
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ans = max(ans, matchCache(i, j));
    cout << ans;
    return 0;
}