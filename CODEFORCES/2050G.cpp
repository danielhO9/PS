#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200001];
int dp[200001][3];

void dfs(int v, int p) {
	int cnt = 0;
	vector<int> val;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		val.push_back(max(dp[u][0], dp[u][1]));
		++cnt;
	}
	sort(val.begin(), val.end());
	dp[v][0] = cnt;
	dp[v][1] = 0;
	dp[v][2] = 0;
	if (cnt >= 1) dp[v][1] = val[(int) val.size() - 1] + cnt - 1;
	if (cnt >= 2) dp[v][2] = val[(int) val.size() - 1] + val[(int) val.size() - 2] + cnt - 2;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 2; i <= n; ++i) for (int j = 0; j < 3; ++j) ++dp[i][j];
	int ans = 0;
	for (int i = 1; i <= n; ++i) for (int j = 0; j < 3; ++j) ans = max(ans, dp[i][j]);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}