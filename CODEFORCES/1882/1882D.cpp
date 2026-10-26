#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;

void getInfo(int v, int p, vector<LL>& sz, vector<LL>& dif, vector<vector<int>>& adj, vector<LL>& a) {
	if (v == 1) dif[v] = 0;
	else dif[v] = a[v] ^ a[p];
	sz[v] = 1;
	for (auto u: adj[v]) if (u != p) {
		getInfo(u, v, sz, dif, adj, a);
		sz[v] += sz[u];
	}
}

void dfs(int v, int p, vector<LL>& ans, vector<LL>& sz, vector<LL>& dif, vector<vector<int>>& adj, vector<LL>& a) {
	if (p != 0) ans[v] = ans[p];
	ans[v] -= sz[v] * dif[v];
	ans[v] -= sz[p] * dif[p];
	LL tszp = sz[p], tszv = sz[v], tdifv = dif[v], tdifp = dif[p];
	if (p != 0) {
		sz[p] = n - sz[v];
		sz[v] = n;
		dif[v] = 0;
		dif[p] = a[v] ^ a[p];
	}
	ans[v] += sz[v] * dif[v];
	ans[v] += sz[p] * dif[p];
	for (auto u: adj[v]) if (u != p) dfs(u, v, ans, sz, dif, adj, a);
	if (p != 0) {
		sz[p] = tszp;
		sz[v] = tszv;
		dif[v] = tdifv;
		dif[p] = tdifp;
	}
}

void solve() {
	cin >> n;
	vector<LL> a(n + 1); for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<LL> sz(n + 1), dif(n + 1);
	getInfo(1, 0, sz, dif, adj, a);
	vector<LL> ans(n + 1);
	for (int i = 1; i <= n; ++i) ans[1] += sz[i] * dif[i];
	dfs(1, 0, ans, sz, dif, adj, a);
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}