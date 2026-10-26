#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
vector<int> adj[200001];
int dis[200001];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
		dis[i] = INT32_MAX;
	}
	dis[1] = 0;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
	}
	for (int i = 1; i < n; ++i) adj[i].push_back(i + 1);
	int maxd = 0;
	for (int i = 1; i < n; ++i) {
		if (maxd > i) cout << '0';
		else cout << '1';
		for (int j: adj[i]) {
			dis[j] = min(dis[j], dis[i] + 1);
			maxd = max(maxd, j - dis[j]);
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}