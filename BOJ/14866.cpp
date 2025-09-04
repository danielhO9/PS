#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    int v, c, rev;
};

const int MAX_V = 300001;
vector<Edge> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
bool vis[MAX_V];
int cnt = 0, col = 0;
vector<int> bcc[MAX_V];

void dfs(int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (const auto& edge: adj[v]) if (edge.v != p) {
        int u = edge.v;
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(u, v);
			low[v] = min(low[u], low[v]);
        }
    }
}

void color(int v, int c, int p) {
    if (c > 0) bcc[v].push_back(c);
    vis[v] = true;
    for (auto& edge: adj[v]) {
        int u = edge.v;
        if (low[u] >= ord[v]) {
            if (!vis[u]) bcc[v].push_back(++col);
            
            if (edge.c == 0) {
                edge.c = col;
                adj[u][edge.rev].c = col;
            }
            
            if (!vis[u]) color(u, col, v);
        } else {
            if (c > 0 && edge.c == 0) {
                edge.c = c;
                adj[u][edge.rev].c = c;
            }
            if (!vis[u]) color(u, c, v);
        }
    }
}

// V: maximum vertex + 1
// 1-index
void getBcc(int V) {
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(i, 0);
    for (int i = 1; i < V; ++i) if (!vis[i]) color(i, 0, 0);
}

void addEdge(int u, int v) {
    adj[u].push_back(Edge {v, 0, (int) adj[v].size()});
    adj[v].push_back(Edge {u, 0, (int) adj[u].size() - 1});
}

int N, M;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        addEdge(u, v);
    }
    getBcc(N + 1);
    
    vector<int> ecnt(col + 1), vcnt(col + 1);
    for (int i = 1; i <= N; ++i) for (const auto& edge: adj[i]) ++ecnt[edge.c];
    for (int i = 1; i <= N; ++i) for (int c: bcc[i]) ++vcnt[c];
    for (int i = 1; i <= col; ++i) {
        assert(ecnt[i] % 2 == 0);
        ecnt[i] /= 2;
    }
    vector<bool> isGraph(col + 1);

    int graph = 0;
    for (int i = 1; i <= col; ++i) if (vcnt[i] <= ecnt[i]) {
        ++graph;
        isGraph[i] = true;
    }
    // for (int i = 1; i <= N; ++i) {
    //     for (const auto& j: adj[i]) cout << i << ' ' << j.v << ' ' << j.c << '\n';
    // }
    // for (int i = 1; i <= N; ++i) {
    //     for (int j: bcc[i]) cout << j << ' ';
    //     cout << '\n';
    // }

    ll ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (bcc[i].size() == 1) {
            int deg = adj[i].size();
            if (M - deg == N - 2) {
                ans += i;
            }
        } else {
            int cnt = 0;
            for (int c: bcc[i]) --vcnt[c];
            for (const auto& edge: adj[i]) {
                if (ecnt[edge.c] == vcnt[edge.c] && isGraph[edge.c]) ++cnt;
                --ecnt[edge.c];
            }

            if (cnt == graph) ans += i;

            for (int c: bcc[i]) ++vcnt[c];
            for (const auto& edge: adj[i]) ++ecnt[edge.c];
        }
    }
    cout << ans;
}