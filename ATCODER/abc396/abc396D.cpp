#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
vector<pair<int, ll>> adj[11];
bool vis[11];
ll val[11];
ll ans = LLONG_MAX;

void dfs(int v) {
	if (v == N) {
		ans = min(ans, val[v]);
		return;
	}
	for (auto [u, w]: adj[v]) if (!vis[u]) {
		vis[u] = true;
		val[u] = val[v] ^ w;
		dfs(u);
		vis[u] = false;
		val[u] = 0;
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int u, v; ll w; cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	val[1] = 0; vis[1] = true;
	dfs(1);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}