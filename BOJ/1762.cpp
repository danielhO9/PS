#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

set<int> adj[100001];
int deg[100001];
vector<pair<int, int>> edges;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        ++deg[u];
        ++deg[v];
        edges.push_back(make_pair(u, v));
    }
    ll ans = 0;
    for (auto [u, v]: edges) {
        if (deg[u] > deg[v]) swap(u, v);
        for (auto w: adj[u]) if (adj[v].find(w) != adj[v].end()) ++ans;
    }
    ans /= 3;
    cout << ans;
}