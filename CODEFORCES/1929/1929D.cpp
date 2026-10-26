#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

void dfs(int v, int p, vector<LL>& ans, vector<LL>& one, vector<vector<int>>& adj) {
	for (auto i: adj[v]) if (i != p) dfs(i, v, ans, one, adj);
	ans[v] = 0;
	for (auto i: adj[v]) if (i != p) {
		ans[v] += ans[i] - one[i];
		while (ans[v] < 0) ans[v] += MOD;
		ans[v] %= MOD;
	}
	LL temp = 1;
	for (auto i: adj[v]) if (i != p) {
		temp *= one[i]; temp %= MOD;
	}
	ans[v] += temp; ans[v] %= MOD;
	for (auto i: adj[v]) if (i != p) {
		ans[v] += (one[i] - 1);
		while (ans[v] < 0) ans[v] += MOD;
		ans[v] %= MOD;
	}
	++ans[v]; ans[v] %= MOD;
	one[v] = 1;
	for (auto i: adj[v]) if (i != p) {
		one[v] *= one[i]; one[v] %= MOD;
	}
	++one[v]; one[v] %= MOD;
}

void solve() {
	int n; cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<LL> ans(n + 1), one(n + 1);
	dfs(1, 0, ans, one, adj);
	// for (int i = 1; i <= n; ++i) cout << one[i] << ' ' << ans[i] << '\n';
	cout << ans[1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}