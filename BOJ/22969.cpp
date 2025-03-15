#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[100001];
int deg[100001];
bool vis[100001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++deg[u];
        ++deg[v];
    }
    for (int i = 1; i <= N; ++i) if (!vis[i]) {
        vector<int> tree;
        queue<int> q; q.push(i); vis[i] = true;
        int v = i;
        while (!q.empty()) {
            int here = q.front(); q.pop();
            tree.push_back(here);
            v = here;
            for (auto there: adj[here]) if (!vis[there]) {
                q.push(there); vis[there] = true;
            }
        }
        int sm = 0; for (auto j: tree) sm += deg[j];
        if (sm % 2) { cout << "NIE"; return 0; }
        sm /= 2; if (sm + 1 != tree.size()) { cout << "NIE"; return 0; }
        if (deg[v] != 1) { cout << "NIE"; return 0; }
        if (deg[adj[v][0]] % 2) v = adj[v][0];

        for (auto j: tree) vis[j] = 0;
        int cur = v; vis[cur] = true;
        vector<int> p;
        while (true) {
            int nxt = -1;
            p.push_back(cur); vis[cur] = true;
            for (auto j: adj[cur]) if (!vis[j]) {
                if (deg[j] == 1) vis[j] = true;
                else {
                    if (nxt != -1) { cout << "NIE"; return 0; }
                    else nxt = j;
                }
            }
            if (nxt == -1) break;
            cur = nxt;
        }
        if (deg[cur] % 2 == 0) for (auto j: adj[cur]) if (deg[j] == 1) { p.push_back(j); break; }
        if (p.size() <= 3) { cout << "NIE"; return 0; }
        for (auto j: tree) vis[j] = false;
        for (auto j: p) {
            if (j == p.front() || j == p.back()) {
                if (deg[j] != 1 && deg[j] != 3) { cout << "NIE"; return 0; }
            } else {
                if (deg[j] != 2 && deg[j] != 4) { cout << "NIE"; return 0; }
            }
            vis[j] = true;
        }
        for (auto j: p) {
            for (auto k: adj[j]) if (!vis[k]) {
                if (deg[k] != 1) { cout << "NIE"; return 0; }
                vis[k] = true;
            }
        }
        
    }
    cout << "TAK";
}