#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int V;
vector<int> adj[10];
ll dp[10];

void dfs(int v, int p) {
    dp[v] = 1;
    for (auto u: adj[v]) if (u != p) {
        dfs(u, v);
        dp[v] *= (dp[u] + 1);
    }
}

void solve() {
    for (int i = 0; i < V - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    ll ans = 0;
    for (int i = 0; i < V; ++i) ans += dp[i];
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int cnt = 0;
    while (true) {
        cin >> V;
        if (!V) break;
        for (int i = 0; i < V; ++i) adj[i].clear();
        cout << "Case " << ++cnt << ": ";
        solve();
    }
}