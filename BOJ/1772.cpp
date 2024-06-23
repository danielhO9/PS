#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[151];
int cache[151][151];
int sz[151];
int par[151], deg[151];
const int MAX = 987654321;

void dfs(int v, int p) {
	sz[v] = 1;
	for (auto u: adj[v]) if (u != p) {
		par[u] = v;
		++deg[v];
		dfs(u, v);
		sz[v] += sz[u];
	}
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cache[i][j] = MAX;
	for (int i = 1; i <= n; ++i) {
		if (i != 1) cache[i][sz[i]] = 1;
		cache[i][0] = 0;
	}
	deque<int> Q;
	for (int i = 1; i <= n; ++i) if (deg[i] == 0) Q.push_back(i);
	while (!Q.empty()) {
		int here = Q.front(); Q.pop_front();
		int there = par[here];
		for (int i = sz[there]; i >= 0; --i) {
			for (int j = 0; j <= sz[here]; ++j) {
				if (i < j) break;
				cache[there][i] = min(cache[there][i], cache[here][j] + cache[there][i - j]);
			}
		}
		--deg[there];
		if (deg[there] == 0) Q.push_back(there);
	}
	int ans = MAX;
	for (int i = 1; i <= n; ++i) {
		if (i == 1) ans = min(ans, cache[i][n - m]);
		else if (sz[i] >= m) ans = min(ans, cache[i][sz[i] - m] + 1);
	}
	if (ans == MAX) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}