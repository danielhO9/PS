#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 100001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
bool vis[MAX_V];
int cnt = 0, col = 0;
vector<int> bcc[MAX_V];
int bccv[MAX_V], bcce[MAX_V];

void dfs(int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(u, v);
			low[v] = min(low[u], low[v]);
        }
    }
}

void color(int v, int c, int p) {
    if (c > 0) {
        bcc[v].push_back(c);
        ++bccv[c];
    }
    vis[v] = true;
    for (auto u: adj[v]) if (u != p) {
        if (vis[u]) {
            if (*lower_bound(bcc[u].begin(), bcc[u].end(), c) == c) ++bcce[c];
            continue;
        }
        if (low[u] >= ord[v]) {
            bcc[v].push_back(++col);
            ++bccv[col]; ++bcce[col];
            color(u, col, v);
        } else {
            ++bcce[c];
            color(u, c, v);
        }
    }
}

// V: maximum vertex + 1
// TODO: 1-index
void getBcc(int V) {
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(i, 0);
    for (int i = 1; i < V; ++i) if (!vis[i]) color(i, 0, 0);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    while (M--) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    getBcc(N + 1);
    for (int i = 1; i <= col; ++i) {
        if (bccv[i] >= 3 && bcce[i] != bccv[i]) {
            cout << "Not cactus";
            return 0;
        }
    }
    for (int i = 1; i <= N; ++i) {
        cnt = 0;
        for (int j: bcc[i]) if (bccv[j] >= 3) ++cnt;
        if (cnt > 1) {
            cout << "Not cactus";
            return 0;
        }
    }
    cout << "Cactus";
}