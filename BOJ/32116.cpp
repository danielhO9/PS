#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<int> adj[200001];
int col[200001];
int con[5][5];
vector<int> cord;

// v, l, r: colored triangle
void dfs(int v, int l, int r) {
    if (l + 1 == r) return;
    if (adj[l].back() != r) adj[l].push_back(r);
    for (int i = (int) adj[l].size() - 1; i > 0; --i) {
        int nr = adj[l][i], nl = adj[l][i - 1];
        col[nl] = cord[0] + cord[1] + cord[2] - col[nr] - col[l];
        dfs(l, nl, nr);
        if (nl == l + 1) break;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= N; ++i) col[i] = -1;
    for (int i = 1; i <= 4; ++i) for (int j = 1; j <= 4; ++j) if (i != j) con[i][j] = 1;
    for (int i = 0; i < K; ++i) {
        int c, d; cin >> c >> d;
        con[c][d] = 0; con[d][c] = 0;
    }
    for (int i = 1; i <= 4; ++i) {
        bool flag = true;
        for (int j = 1; j <= 4; ++j) if (j != i) {
            for (int k = 1; k <= 4; ++k) if (k != i && k != j) {
                if (!con[j][k]) flag = false;
            }
        }
        if (flag) {
            for (int j = 1; j <= 4; ++j) if (j != i) cord.push_back(j);
            break;
        }
    }
    if (cord.empty()) {
        for (int i = 1; i <= 4; ++i) {
            if (!cord.empty()) break;
            for (int j = 1; j <= 4; ++j) if (i != j) {
                if (con[i][j]) {
                    cord.push_back(i);
                    cord.push_back(j);
                    break;
                }
            }
        }
    }
    if (cord.empty()) {
        cout << -1;
        return 0;
    }
    if (cord.size() == 2) {
        for (int i = 1; i <= N; ++i) if (col[i] == -1) {
            queue<int> q; q.push(i); col[i] = cord[0];
            while (!q.empty()) {
                int here = q.front(); q.pop();
                for (auto there: adj[here]) if (col[there] == -1) {
                    q.push(there);
                    col[there] = cord[0] + cord[1] - col[here];
                }
            }
        }
        bool flag = true;
        for (int i = 1; i <= N; ++i) {
            for (int j: adj[i]) if (col[i] == col[j]) {
                flag = false;
                break;
            }
        }
        if (flag) for (int i = 1; i <= N; ++i) cout << col[i] << ' ';
        else cout << -1;
        return 0;
    }
    for (int i = 1; i <= N; ++i) {
        int tar = i + 1;
        if (tar == N + 1) tar = 1;
        bool flag = false;
        for (int j: adj[i]) if (j == tar) flag = true;
        if (!flag) adj[i].push_back(tar);
        tar = i - 1;
        if (tar == 0) tar = N;
        flag = false;
        for (int j: adj[i]) if (j == tar) flag = true;
        if (!flag) adj[i].push_back(tar);
        sort(adj[i].begin(), adj[i].end());
    }
    col[1] = cord[0];
    for (int i = (int) adj[1].size() - 1; i > 0; --i) {
        if (col[adj[1][i]] == -1) col[adj[1][i]] = cord[1];
        col[adj[1][i - 1]] = cord[1] + cord[2] - col[adj[1][i]];
        dfs(1, adj[1][i - 1], adj[1][i]);
    }
    for (int i = 1; i <= N; ++i) cout << col[i] << ' ';
}