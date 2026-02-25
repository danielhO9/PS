#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[200001];
set<int> flags[200001];
bool marked[200001];
bool done[200000];
set<int> tmp;

void dfs(int v, int p) {
    for (int u: adj[v]) if (u != p) dfs(u, v);
    
    tmp.clear();
    for (auto i: flags[v]) if (!done[i]) tmp.insert(i);
    swap(tmp, flags[v]);
    for (int u: adj[v]) if (u != p) {
        if (flags[u].size() > flags[v].size()) {
            swap(flags[u], flags[v]);
        }
        for (auto i: flags[u]) if (!done[i]) {
            if (flags[v].find(i) != flags[v].end()) {
                done[i] = true;
                marked[v] = true;
            }
            flags[v].insert(i);
        }
    }
    if (marked[v]) {
        for (auto i: flags[v]) done[i] = true;
        flags[v].clear();
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        if (u == v) {
            marked[u] = true;
            done[i] = true;
            continue;
        }
        flags[u].insert(i);
        flags[v].insert(i);
    }

    dfs(1, 0);

    int ans = 0;
    for (int i = 1; i <= n; ++i) if (marked[i]) ++ans;
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) if (marked[i]) cout << i << ' ';
}