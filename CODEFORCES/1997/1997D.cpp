#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[200001];
vector<int> adj[200001];

ll bfs(int v) {
	if (adj[v].empty()) return a[v];
	if (v == 1) {
		ll ret = LLONG_MAX;
		for (auto u: adj[v]) {
			ret = min(ret, bfs(u));
		}
		return a[v] + ret;
	}
	ll ret = LLONG_MAX;
	for (auto u: adj[v]) {
		ret = min(ret, bfs(u));
	}
	if (ret >= a[v]) {
		ret += a[v];
		return ret / 2ll;
	}
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		adj[p].push_back(i);
	}
	cout << bfs(1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}