#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll Q, M, N;

tuple<int, int, ll> dis[1000][1000][20];
int f[1000];
ll vis[1000][1000];
pair<int, int> start;
ll tos, cyc;

void init() {
    for (int i = 0; i < M; ++i) {
        if (i < 10) f[i] = 1;
        else if (i < 100) f[i] = 2;
        else f[i] = 3;
    }
    for (int i = 0; i < M; ++i) for (int j = 0; j < M; ++j) {
        dis[i][j][0] = {j, (i + j) % M, f[j]};
    }
    for (int k = 1; k < 20; ++k) {
        for (int i = 0; i < M; ++i) for (int j = 0; j < M; ++j) {
            auto [ni, nj, d] = dis[i][j][k - 1];
            auto [nii, njj, dd] = dis[ni][nj][k - 1];
            dis[i][j][k] = {nii, njj, dd + d};
        }
    }
    memset(vis, -1, sizeof(vis));
    pair<int, int> cur = make_pair(0, 1); vis[0][1] = 0;
    ll path = 0;
    while (true) {
        auto [i, j, d] = dis[cur.first][cur.second][0];
        path += d;
        if (vis[i][j] != -1) {
            start = make_pair(i, j);
            cyc = path - vis[i][j];
            tos = vis[i][j];
            break;
        }
        cur.first = i, cur.second = j;
    }
    // cout << tos << ' '<< cyc << ' ' << start.first << ' ' << start.second << '\n';
}

void solve() {
    pair<int, int> cur = make_pair(0, 1);

    if (N > tos) {
        N -= tos;
        cur = start;
        N %= cyc;
    }

    for (int i = 19; i >= 0; --i) {
        auto [ni, nj, d] = dis[cur.first][cur.second][i];
        if (d <= N) {
            N -= d;
            cur.first = ni;
            cur.second = nj;
        }
    }
    while (f[cur.second] <= N) {
        // cout << cur.first << ' ' << cur.second << ' ' << N << '\n';
        auto [ni, nj, d] = dis[cur.first][cur.second][0];
        N -= d;
        cur.first = ni;
        cur.second = nj;
    }
    string s = to_string(cur.second);
    cout << s[N] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> Q >> M;
    init();
    for (int i = 0; i < Q; ++i) {
        cin >> N;
        --N;
        solve();
    }
}