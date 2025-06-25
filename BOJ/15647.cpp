#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<pair<int, ll>> adj[300001];
ll sz[300001];
ll ans[300001];
ll cur;

void dfs(int v, int p) {
    sz[v] = 1;
    for (auto [u, d]: adj[v]) if (u != p) {
        dfs(u, v);
        sz[v] += sz[u];
        cur += sz[u] * d;
    }
}

void dfs2(int v, int p) {
    ans[v] = cur;
    ll tmp = cur;
    for (auto [u, d]: adj[v]) if (u != p) {
        cur -= sz[u] * d;
        cur += (N - sz[u]) * d;
        dfs2(u, v);
        cur = tmp;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v; ll d; cin >> u >> v >> d;
        adj[u].push_back(make_pair(v, d));
        adj[v].push_back(make_pair(u, d));
    }
    cur = 0;
    dfs(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= N; ++i) cout << ans[i] << '\n';
}