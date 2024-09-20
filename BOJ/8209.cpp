#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int v;
	int cnt;
	int rev;
};

int n, m;
vector<Edge> adj[100001];
int last[100001];
vector<vector<int>> ans;

void dfs(int v) {
	while (last[v] < adj[v].size()) {
		if (adj[v][last[v]].cnt == 0) {
			++last[v];
			continue;
		}
		--adj[v][last[v]].cnt;
		--adj[adj[v][last[v]].v][adj[v][last[v]].rev].cnt;
		// ++last[v];
		dfs(adj[v][last[v]].v);
	}
	ans.back().push_back(v);
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, s, t; cin >> a >> b >> s >> t;
		if (s + t == 1) {
			// cout << a << ' ' << b << '\n';
			adj[a].push_back({b, 1, (int) adj[b].size()});
			adj[b].push_back({a, 1, (int) adj[a].size() - 1});
		}
	}
	for (int i = 1; i <= n; ++i) {
		int cnt = 0;
		if (adj[i].size() % 2) {
			cout << "NIE";
			return;
		}
	}
	for (int i = 1; i <= n; ++i) {
		// while (last[i] < adj[i].size() && adj[i][last[i]].cnt == 0) ++last[i];
		if (last[i] < adj[i].size()) {
			ans.push_back({});
			dfs(i);
		}
	}
	cout << ans.size() << '\n';
	for (auto& i: ans) {
		cout << (int)i.size() - 1 << ' ';
		for (auto j: i) cout << j << ' ';
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}