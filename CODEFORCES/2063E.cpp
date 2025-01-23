#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[300001];
multiset<ll> ways[300001];
ll add[300001];
ll ans;

void dfs(int v, int p) {
	add[v] = 0;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		ways[u].insert(-add[u]);
		++add[u];
		if (ways[v].size() < ways[u].size()) {
			swap(ways[v], ways[u]);
			swap(add[v], add[u]);
		}
		auto itr = ways[v].begin();
		ll cnt = ways[v].size();
		for (auto i: ways[u]) {
			if (itr == ways[v].end()) break;
			ll val = i + add[u] - add[v];
			while (itr != ways[v].end() && (*itr) < val) {
				++itr;
				--cnt;
			}
			ans += (2 * (i + add[u]) - 1) * cnt;
		}
		itr = ways[u].begin();
		cnt = ways[u].size();
		for (auto i: ways[v]) {
			if (itr == ways[u].end()) break;
			ll val = i + add[v] - add[u];
			while (itr != ways[u].end() && (*itr) <= val) {
				++itr;
				--cnt;
			}
			ans += (2 * (i + add[v]) - 1) * cnt;
		}
		for (auto i: ways[u]) {
			ll val = i + add[u] - add[v];
			ways[v].insert(val);
		}
	}
	// cout << v << '\n';
	// if (!ways[v].empty()) {
	// 	for (auto i: ways[v]) cout << i + add[v] << ' ';
	// 	cout << '\n';
	// }
	// else cout << "empty\n";
}

/*
5: {1}, {1, 2, 3} -> 1 * 3 = 3
4: {1, 2, 2, 3, 4}, {1, 2} -> 1 * 5 + 3 * 4 = 17
2: {1}, {1, 2, 2, 3, 3, 3, 4, 5} -> 1 * 8 = 8
*/

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) ways[i].clear();
	ans = 0;
	dfs(1, 0);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}