#include <bits/stdc++.h>
using namespace std;

int dz[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dx[6] = {0, 0, 0, 0, 1, -1};

void solve() {
    int r, f, c; cin >> r >> f >> c;
    int arr[r][f][c], dis[r][f][c];
    memset(arr, 0, sizeof(arr));
    memset(dis, -1, sizeof(dis));
    tuple<int, int, int> s, e;
    for (int i = 0; i < r; ++i) for (int j = 0; j < f; ++j) {
        string ss; cin >> ss;
        for (int k = 0; k < c; ++k) {
            if (ss[k] == '#') arr[i][j][k] = 1;
            else if (ss[k] == 'S') s = {i, j, k};
            else if (ss[k] == 'E') e = {i, j, k};
        }
    }
    dis[get<0>(s)][get<1>(s)][get<2>(s)] = 0;
    deque<tuple<int, int, int>> q; q.push_front(s);
    while (!q.empty()) {
        auto [i, j, k] = q.front(); q.pop_front();
        for (int l = 0; l < 6; ++l) {
            int ni = i + dz[l], nj = j + dy[l], nk = k + dx[l];
            if (0 <= ni && ni < r && 0 <= nj && nj < f && 0 <= nk && nk < c) {
                if (dis[ni][nj][nk] == -1 || dis[ni][nj][nk] > dis[i][j][k] + arr[ni][nj][nk]) {
                    dis[ni][nj][nk] = dis[i][j][k] + arr[ni][nj][nk];
                    if (arr[ni][nj][nk]) q.push_back({ni, nj, nk});
                    else q.push_front({ni, nj, nk});
                }
            }
        }
    }
    cout << dis[get<0>(e)][get<1>(e)][get<2>(e)] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}