#include <bits/stdc++.h>
using namespace std;

int T;
string arr[12];
bool vis[12][10];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

void move(int y, int x) {
    char c = arr[y][x];
    // cout << c << '\n';
    if (c == ' ') return;
    int cnt = 1;
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int>> q;
    q.push(make_pair(y, x)); vis[y][x] = true;
    while (!q.empty()) {
        auto [yy, xx] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = yy + dy[i], nx = xx + dx[i];
            if (0 <= ny && ny < 12 && 0 <= nx && nx < 10 && arr[ny][nx] == c && !vis[ny][nx]) {
                // arr[ny][nx] = ' ';
                q.push(make_pair(ny, nx));
                vis[ny][nx] = true;
                ++cnt;
            }
        }
    }
    if (cnt <= 2) return;
    q.push(make_pair(y, x)); arr[y][x] = ' ';
    while (!q.empty()) {
        auto [yy, xx] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = yy + dy[i], nx = xx + dx[i];
            if (0 <= ny && ny < 12 && 0 <= nx && nx < 10 && arr[ny][nx] == c) {
                arr[ny][nx] = ' ';
                q.push(make_pair(ny, nx));
            }
        }
    }
    for (int j = 0; j < 10; ++j) {
        vector<char> v;
        for (int i = 0; i < 12; ++i) if (arr[i][j] != ' ') v.push_back(arr[i][j]);
        for (int i = 0; i < 12; ++i) {
            if (i < v.size()) arr[i][j] = v[i];
            else arr[i][j] = ' ';
        }
    }
    for (int j = 1; j < 10; ++j) if (arr[0][j] != ' ') {
        int cur = j;
        while (cur > 0 && arr[0][cur - 1] == ' ') {
            for (int i = 0; i < 12; ++i) swap(arr[i][cur], arr[i][cur - 1]);
            --cur;
        }
    }
    // for (int i = 11; i >= 0; --i) {
    //     cout << arr[i] << '\n';
    // }
    // cout << '\n';
}

void solve() {
    for (int i = 0; i < 12; ++i) cin >> arr[11 - i];
    for (int i = 0; i < T; ++i) {
        char c; int y; cin >> c >> y;
        move(y - 1, c - 'a');
    }
    int ans = 0;
    for (int i = 0; i < 12; ++i) for (int j = 0; j < 10; ++j) if (arr[i][j] != ' ') ++ans;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> T;
        if (T == 0) break;
        solve();
    }
}