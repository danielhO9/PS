#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 993244853;

struct Move {
    pair<int, int> pos, neg, d;
};

vector<Move> moves;
int nxt[1000][1000];
int inv[1000][1000];
bool reach[1000][1000];
bool vis[1000][1000];
bool rec[1000][1000];
int deg[1000][1000];
ll ans[1000][1000];
int N, M;

void dfs1(int i, int j) {
    if (reach[i][j]) return;
    reach[i][j] = true;
    for (int k = 0; k < 10; ++k) if ((inv[i][j] >> k) & 1) {
        int ni = i - moves[k].d.first;
        int nj = j - moves[k].d.second;
        dfs1(ni, nj);
    }
}

bool dfs2(int i, int j) {
    if (rec[i][j]) return true;
    if (vis[i][j]) return false;

    vis[i][j] = true;
    rec[i][j] = true;
    for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
        int ni = i + moves[k].d.first;
        int nj = j + moves[k].d.second;
        if (dfs2(ni, nj)) return true;
    }
    rec[i][j] = false;
    return false;
}

void dfs3(int i, int j) {
    if (reach[i][j]) return;
    reach[i][j] = true;
    for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
        int ni = i + moves[k].d.first;
        int nj = j + moves[k].d.second;
        dfs3(ni, nj);
    }
}

void solve() {
    for (int i = 0; i < 10; ++i) {
        string s; cin >> s;
        pair<int, int> cur = make_pair(0, 0);
        pair<int, int> pos = make_pair(0, 0), neg = make_pair(0, 0);
        for (auto j: s) {
            if (j == 'N') --cur.first;
            else if (j == 'S') ++cur.first;
            else if (j == 'W') --cur.second;
            else ++cur.second;
            pos.first = max(pos.first, cur.first);
            pos.second = max(pos.second, cur.second);
            neg.first = min(neg.first, cur.first);
            neg.second = min(neg.second, cur.second);
        }
        moves.push_back({pos, neg, cur});
    }
    cin >> N >> M;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < 10; ++k) {
        if (i == N - 1 && j == M - 1) continue;
        int ni = i + moves[k].pos.first;
        int nj = j + moves[k].pos.second;
        if (ni >= N || nj >= M) continue;
        ni = i + moves[k].neg.first;
        nj = j + moves[k].neg.second;
        if (ni < 0 || nj < 0) continue;
        nxt[i][j] ^= (1 << k);
        inv[i + moves[k].d.first][j + moves[k].d.second] ^= (1 << k);
    }
    dfs1(N - 1, M - 1);
    if (!reach[0][0]) {
        cout << 0;
        return;
    }
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        if (!reach[i][j]) {
            nxt[i][j] = 0;
            continue;
        }
        for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
            int ni = i + moves[k].d.first;
            int nj = j + moves[k].d.second;
            if (!reach[ni][nj]) nxt[i][j] ^= (1 << k);
        }
    }
    memset(reach, 0, sizeof(reach));
    dfs3(0, 0);
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        if (!reach[i][j]) {
            nxt[i][j] = 0;
            continue;
        }
        for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
            int ni = i + moves[k].d.first;
            int nj = j + moves[k].d.second;
            if (!reach[ni][nj]) nxt[i][j] ^= (1 << k);
            else ++deg[ni][nj];
        }
    }
    // for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    //     cout << i * M + j << ": ";
    //     for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
    //         int ni = i + moves[k].d.first;
    //         int nj = j + moves[k].d.second;
    //         cout << ni * M + nj << ' ';
    //     }
    //     cout << '\n';
    // }
    if (dfs2(0, 0)) {
        cout << -1;
        return;
    }
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    ans[0][0] = 1ll;
    while (!q.empty()) {
        int i = q.front().first, j = q.front().second;
        // for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cout << deg[i][j] << ' ';
        // cout << '\n';
        q.pop();
        for (int k = 0; k < 10; ++k) if ((nxt[i][j] >> k) & 1) {
            int ni = i + moves[k].d.first;
            int nj = j + moves[k].d.second;
            ans[ni][nj] += ans[i][j];
            ans[ni][nj] %= MOD;
            --deg[ni][nj];
            if (deg[ni][nj] == 0) {
                q.push(make_pair(ni, nj));
            }
        }
    }
    // for (int i = 0; i < N; ++i) {
    //     for (int j = 0; j < M; ++j) cout << ans[i][j] << ' ';
    //     cout << '\n';
    // }
    cout << ans[N - 1][M - 1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}