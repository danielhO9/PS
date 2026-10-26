#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
vector<int> adj[200001];
ll l[200001], r[200001];
ll opt[200001];
ll add;

void dfs(int v, int p) {
	opt[v] = l[v];
	ll mx = -1;
	bool right = false;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		if (r[v] < opt[u]) {
			right = true;
			add += opt[u] - r[v];
		}
		mx = max(mx, opt[u]);
	}
	if (mx == -1) return;
	if (right) opt[v] = r[v];
	else opt[v] = max(l[v], mx);
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) cin >> l[i] >> r[i];
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	add = 0;
	dfs(1, 0);
	cout << add + opt[1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}