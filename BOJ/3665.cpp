#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int rank[n + 1];
	for (int i = 1; i <= n; ++i) {
		int temp; cin >> temp;
		rank[temp] = i;
	}
	int m; cin >> m;
	vector<int> adj[n + 1];
	bool vis[n + 1][n + 1]; memset(vis, false, sizeof(vis));
	int deg[n + 1]; memset(deg, 0, sizeof(deg));
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b;
		vis[min(a, b)][max(a, b)] = true;
		if (rank[a] < rank[b]) {
			adj[b].push_back(a);
			++deg[a];
		}
		else {
			adj[a].push_back(b);
			++deg[b];
		}
	}
	for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
		if (vis[i][j]) continue;
		if (rank[i] < rank[j]) {
			adj[i].push_back(j);
			++deg[j];
		} else {
			adj[j].push_back(i);
			++deg[i];
		}
	}
	deque<int> Q;
	vector<int> ans;
	for (int i = 1; i <= n; ++i) if (deg[i] == 0) Q.push_back(i);
	for (int i = 1; i <= n; ++i) {
		if (Q.size() == 0) {
			cout << "IMPOSSIBLE\n";
			return;
		}
		if (Q.size() >= 2) {
			cout << "?\n";
			return;
		}
		int here = Q.front(); Q.pop_front();
		ans.push_back(here);
		for (auto there: adj[here]) {
			--deg[there];
			if (deg[there] == 0) {
				Q.push_back(there);
			}
		}
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}