#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll c[200000];
vector<ll> adj[200000];
ll ans = 0;
ll color[200001];

void dfs(ll v, ll p) {
	ans += color[c[v]];
	ll temp = color[c[v]];
	for (auto u: adj[v]) if (u != p) {
		color[c[v]] = 1;
		dfs(u, v);
	}
	color[c[v]] = temp + 1;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> c[i];
	for (int i = 0; i < n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) color[i] = 0;
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v; --u; --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	ans = 0;
	dfs(0, -1);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}