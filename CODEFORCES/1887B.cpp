#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, t; cin >> n >> t;
	vector<pair<int, int>> graph[n + 1];
	for (int i = 1; i <= t; ++i) {
		int m; cin >> m;
		for (int j = 0; j < m; ++j) {
			int u, v; cin >> u >> v;
			graph[u].push_back({v, i});
			graph[v].push_back({u, i});
		}
	}
	int k; cin >> k; vector<int> moments[t + 1];
	for (int i = 1; i <= k; ++i) {
		int a; cin >> a;
		moments[a].push_back(i);
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push({0, 1});
	int dis[n + 1]; for (int i = 1; i <= n; ++i) dis[i] = INT32_MAX; dis[1] = 0;
	while (!Q.empty()) {
		pair<int, int> here = Q.top(); Q.pop();
		if (dis[here.second] < here.first) continue;
		if (here.second == n) {
			cout << here.first << '\n';
			return;
		}
		for (auto there: graph[here.second]) {
			auto ite = lower_bound(moments[there.second].begin(), moments[there.second].end(), here.first + 1);
			if (ite == moments[there.second].end() || dis[there.first] <= *ite) continue;
			dis[there.first] = *ite;
			Q.push({*ite, there.first});
		}
	}
	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}