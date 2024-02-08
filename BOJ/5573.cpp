#include <bits/stdc++.h>
using namespace std;
int H, W, N, cache[2][1000][1000];
int moveToRight[1000][1000], temp;

int matchCache(int way, int i, int j) {
    if (i == 0 && j == 0) {
        if (way == moveToRight[0][0]) return N % 2 == 0 ? N / 2 : (N / 2) + 1;
        else return N / 2;
    }
    int& ret = cache[way][i][j];
    if (ret != -1) return ret;
    ret = 0;
    if (j - 1 >= 0) ret += matchCache(1, i, j - 1);
    if (i - 1 >= 0) ret += matchCache(0, i - 1, j);
    if (way == moveToRight[i][j] && ret % 2 != 0) { ret /= 2; ++ret; }
    else ret /= 2;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> H >> W >> N;
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) cin >> moveToRight[i][j];
    memset(cache, -1, sizeof(cache));
    int y = 0, x = 0; --N;
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) { matchCache(0, i, j); matchCache(1, i, j); }
    while (true) {
        temp = moveToRight[y][x];
        if ((matchCache(0, y, x) + matchCache(1, y, x)) % 2 == 0) {
            x += temp; y += (1 - temp);
        } else {
            x += (1 - temp); y += temp;
        }
        if (y == H || x == W) break;
    }
    cout << y + 1 << " " << x + 1;
    return 0;
}
