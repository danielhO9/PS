#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[200001];
ll deg[200001];
ll dis[200001];
ll tcnt[200001];
ll par[200001];

void dfs(int v, int p) {
	tcnt[v] = (dis[v] >= 2);
	par[v] = p;
	for (int u: adj[v]) if (u != p) {
		dfs(u, v);
		tcnt[v] += tcnt[u];
	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) dis[i] = -1;
	for (int i = 1; i <= n; ++i) deg[i] = 0;
	for (int i = 1; i <= n; ++i) {
		par[i] = 0;
		tcnt[i] = 0;
	}

	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		++deg[u]; ++deg[v];
	}
	queue<int> q;
	for (int i = 1; i <= n; ++i) if (deg[i] == 1) {
		q.push(i);
		dis[i] = 0;
	}
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int u: adj[v]) if (dis[u] == -1) {
			dis[u] = dis[v] + 1;
			q.push(u);
		}
	}
	dfs(1, 0);
	ll ans = 0;
	ll zcnt = 0;
	for (int i = 1; i <= n; ++i) if (dis[i] == 0) ++zcnt;
	// cout << zcnt << '\n';
	ans += zcnt * (n - zcnt);
	for (int i = 1; i <= n; ++i) if (dis[i] >= 1) {
		for (int j: adj[i]) if (dis[j] == 1) {
			if (j == par[i]) {
				ans += (tcnt[1] - tcnt[i]);
			} else {
				ans += tcnt[j];
			}
		}
	}

	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}