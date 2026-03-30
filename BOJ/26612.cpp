#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Strongly Connected Components (SCC) using Kosaraju's Algorithm.
 *  Finds all SCCs in a directed graph.
 * Time: O(V + E), where V is the number of vertices and E is the number of edges.
 */
const int MAX_V = 300001;
vector<int> adj[MAX_V];

vector<int> iadj[MAX_V];
bool vis[MAX_V];

void dfs(vector<int>& ord, int v) {
    vis[v] = true;
    for (auto u: adj[v]) if (!vis[u]) dfs(ord, u);
    ord.push_back(v);
}

void idfs(vector<vector<int>>& ret, int v) {
    vis[v] = true;
    ret.back().push_back(v);
    for (auto u: iadj[v]) if (!vis[u]) idfs(ret, u);
}

// V: maximum vertex + 1
vector<vector<int>> getScc(int V) {
    const int s = 1; // 1-index
    for (int u = s; u < V; ++u) for (auto v: adj[u]) iadj[v].push_back(u);
    vector<int> ord;
    for (int i = s; i < V; ++i) if (!vis[i]) dfs(ord, i);
    reverse(ord.begin(), ord.end());
    for (int i = s; i < V; ++i) vis[i] = false;
    vector<vector<int>> ret;
    for (auto v: ord) if (!vis[v]) {
        ret.push_back({});
        idfs(ret, v);
    }
    return ret;
}

int N, M, Q;
int in[MAX_V], out[MAX_V];
int cnt = 0;

void dfs2(int v) {
    in[v] = ++cnt;
    for (auto u: iadj[v]) dfs2(u);
    out[v] = cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> Q;
    for (int i = 0; i < M; ++i) {
        int u, v; char c; cin >> u >> v >> c;
        if (c == 'x') adj[2 * N + u].push_back(v);
        else if (c == 'y') adj[u].push_back(N + v);
        else adj[N + u].push_back(2 * N + v);
    }
    bool cyc = false;
    auto scc = getScc(3 * N + 1);
    if (scc.size() < 3 * N) cyc = true;

    for (int i = 1; i <= 3 * N; ++i) if (adj[i].empty()) dfs2(i);

    while (Q--) {
        int u, v; char c; cin >> u >> v >> c;
        if (c == 'x') u += 2 * N;
        else if (c == 'y') v += N;
        else {
            u += N;
            v += 2 * N;
        }
        if (cyc) {
            cout << 1 << '\n';
            continue;
        }
        if (in[u] <= in[v] && in[v] <= out[u]) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}