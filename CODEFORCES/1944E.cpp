#include <bits/stdc++.h>
using namespace std;

void dfs(int v, int p, vector<vector<int>>& adj, vector<int>& dep, vector<int>& par) {
	par[v] = p; dep[v] = dep[p] + 1;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v, adj, dep, par);
	}
}

void solve() {
	int n; cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> dep(n + 1), par(n + 1);
	dep[0] = 0; dfs(1, 0, adj, dep, par);
	int u = max_element(dep.begin(), dep.end()) - dep.begin();
	dfs(u, 0, adj, dep, par);
	int v = max_element(dep.begin(), dep.end()) - dep.begin();
	if (dep[v] % 4 == 0) {
		int c1 = v;
		for (int i = 0; i < dep[v] / 2 - 1; ++i) c1 = par[c1];
		int c2 = par[c1];
		cout << dep[v] / 2 << '\n';
		for (int i = 1; i < dep[v] / 2; i += 2) {
			cout << c1 << ' ' << i << '\n';
			cout << c2 << ' ' << i << '\n';
		}
		return;
	}
	int c = v;
	for (int i = 0; i < dep[v] / 2; ++i) c = par[c];
	cout << dep[v] / 2 + 1 << '\n';
	for (int i = 0; i < dep[v] / 2 + 1; ++i) {
		cout << c << ' ' << i << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}