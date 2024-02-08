#include <bits/stdc++.h>
using namespace std;
int R, C, cache[4][750][750];
int mine[750][750];
int dx[4] = {1, -1, -1, 1}, dy[4] = {-1, -1, 1, 1};
string temp;

int matchCache(int id, int i, int j) {
    if (i < 0 || i >= R || j < 0 || j >= C) return 0;
    int& ret = cache[id][i][j];
    if (ret != -1) return ret;
    if (mine[i][j] == 0) return 0;
    ret = 1;
    if (mine[i + dy[id]][j + dx[id]] != 0) ret += matchCache(id, i + dy[id], j + dx[id]);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> R >> C;
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < R; ++i) {
        cin >> temp;
        for (int j = 0; j < temp.size(); ++j) mine[i][j] = (int) temp[j] - 48;
    }
    int ans = 0;
    for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
        for (int size = min(matchCache(2, i, j), matchCache(3, i, j)); size > 0; --size) {
            if (size <= ans) break;
            if (min(matchCache(0, i + size * 2 - 2, j), matchCache(1, i + size * 2 - 2, j)) >= size) {
                ans = size; break;
            }
        }
    }
    cout << ans;
    return 0;
}