#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<vector<int>> adj(n + 1);
	vector<int> cnt(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		++cnt[u];
		++cnt[v];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) if (cnt[i] == 1) ++ans;
	cout << (ans + 1) / 2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}