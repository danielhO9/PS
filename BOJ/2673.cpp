#include <bits/stdc++.h>
using namespace std;
int N, cache[101][101];
bool line[101][101];

int matchCache(int l, int r) {
    if (r - l == 1) {
        if (line[l][r]) return 1;
        else return 0;
    }
    int& ret = cache[l][r];
    if (ret != -1) return ret;
    ret = 0;
    for (int i = l + 1; i < r; ++i) ret = max(ret, matchCache(l, i) + matchCache(i, r));
    if (line[l][r]) ret += 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int x, y;
    for (int i = 0; i < N; ++i) {
        cin >> x >> y;
        line[x][y] = 1; line[y][x] = 1;
    }
    memset(cache, -1, sizeof(cache));
    cout << matchCache(1, 100);
}