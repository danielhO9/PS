#include <bits/stdc++.h>
using namespace std;

const int MAX = 987654321;

int H, W;
string arr[50];
int d[50][50];
int dis[16][16];
int sdis[16];
int dp[1 << 16][16];
map<pair<int, int>, int> m;
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

void bfs(int y, int x) {
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) d[i][j] = MAX;
    d[y][x] = 0;
    queue<pair<int, int>> q; q.push(make_pair(y, x));
    while (!q.empty()) {
        auto [yy, xx] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = yy + dy[i], nx = xx + dx[i];
            if (0 <= ny && ny < H && 0 <= nx && nx < W && arr[ny][nx] != 'X' && d[ny][nx] == MAX) {
                d[ny][nx] = d[yy][xx] + 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    if (arr[y][x] == 'U') {
        for (auto [i, j]: m) sdis[j] = d[i.first][i.second];
    } else {
        int h = m[make_pair(y, x)];
        for (auto [i, j]: m) dis[h][j] = d[i.first][i.second];
    }
}

void solve() {
    cin >> H >> W;
    for (int i = 0; i < H; ++i) cin >> arr[i];
    m.clear();
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (arr[i][j] == '#') {
        m[make_pair(i, j)] = m.size();
    }
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (arr[i][j] == '#' || arr[i][j] == 'U') {
        bfs(i, j);
    }
    int n = m.size();
    for (int i = 0; i < (1 << n); ++i) for (int j = 0; j < n; ++j) dp[i][j] = MAX;
    for (int i = 0; i < n; ++i) dp[1 << i][i] = sdis[i];
    // for (int i = 0; i < n; ++i) cout << sdis[i] << ' ';
    // cout << '\n';
    vector<int> ord[n + 1];
    for (int i = 0; i < (1 << n); ++i) ord[__builtin_popcount(i)].push_back(i);
    for (int i = 1; i < n; ++i) {
        for (auto mask: ord[i]) for (int s = 0; s < n; ++s) {
            for (int e = 0; e < n; ++e) if (!(mask >> e & 1)) {
                dp[mask ^ (1 << e)][e] = min(dp[mask ^ (1 << e)][e], dp[mask][s] + dis[s][e]);
            }
        }
    }
    int ans = MAX;
    for (int i = 0; i < n; ++i) ans = min(ans, dp[(1 << n) - 1][i]);
    if (ans == MAX) cout << "impossible\n";
    else cout << ans + n << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}