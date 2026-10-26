#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int H, W;
char A[500][500];
int cache[500][500][2];

struct Node {
    int h, w, t;
};

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void solve() {
    cin >> H >> W;
    for (int i = 0; i < H; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W; ++j) A[i][j] = s[j];
    }
    memset(cache, -1, sizeof(cache));
    queue<Node> q;
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (A[i][j] == 'S') {
        q.push({i, j, 0});
        cache[i][j][0] = 0;
    }
    while (!q.empty()) {
        Node here = q.front(); q.pop();
        if (A[here.h][here.w])
        for (int i = 0; i < 4; ++i) {
            Node there = {here.h + dy[i], here.w + dx[i], here.t};
            if (0 <= there.h && there.h < H && 0 <= there.w && there.w < W) {
                char c = A[there.h][there.w];
                if (c == '#' || (there.t && c == 'o') || (there.t == 0 && c == 'x')) continue;
                if (c == '?') there.t ^= 1;
                if (cache[there.h][there.w][there.t] != -1) continue;
                cache[there.h][there.w][there.t] = cache[here.h][here.w][here.t] + 1;
                q.push(there);
            }
        }
    }
    int ans = INT32_MAX;
    for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (A[i][j] == 'G') {
        for (int k = 0; k < 2; ++k) if (cache[i][j][k] != -1) ans = min(ans, cache[i][j][k]);
    }
    if (ans == INT32_MAX) ans = -1;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}