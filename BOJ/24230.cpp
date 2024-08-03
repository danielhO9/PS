#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> adj[200001];
int C[200001];

int ans = 0;

void dfs(int v, int p) {
	if (p == 0) {
		if (C[v]) ++ans;
		for (int u: adj[v]) if (u != p) dfs(u, v);
		return;
	}
	if (C[v] != C[p]) ++ans;
	for (int u: adj[v]) if (u != p) dfs(u, v);
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> C[i];
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}