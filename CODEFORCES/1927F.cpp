#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

vector<int> ret;
bool found;

void dfs(int v, int p, vector<int>& path, vector<vector<int>>& adj, int& t, bool& found) {
	path.push_back(v);
	if (v == t) {
		ret = path;
		found = true;
		return;
	}
	for (auto i: adj[v]) if (i != p) {
		if (found) return;
		dfs(i, v, path, adj, t, found);
	}
	path.pop_back();

}

void solve() {
	int n, m; cin >> n >> m;
	vector<int> parent(n + 1);
	for (int i = 1; i <= n; ++i) parent[i] = i;
	vector<pair<int, pair<int, int>>> E;
	for (int i = 0; i < m; ++i) {
		int u, v, w; cin >> u >> v >> w;
		E.push_back({w, {u, v}});
	}
	sort(E.rbegin(), E.rend());
	vector<vector<int>> adj(n + 1);
	int b = 987654321;
	pair<int, int> bp;
	for (auto e: E) {
		int u = e.second.first, v = e.second.second;
		if (find(parent, u) == find(parent, v)) {
			b = e.first;
			bp = e.second;
		} else {
			Union(parent, u, v);
			adj[u].push_back(v); adj[v].push_back(u);
		}
	}
	vector<int> path;
	bool found = false;
	dfs(bp.first, 0, path, adj, bp.second, found);
	cout << b << ' ' << ret.size() << '\n';
	for (auto i: ret) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}