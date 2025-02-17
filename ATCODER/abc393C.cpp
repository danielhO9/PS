#include <bits/stdc++.h>
using namespace std;

unordered_set<int> adj[200001];
int N, M;

void solve() {
	cin >> N >> M;
	int ans = 0;
	for (int i = 0; i < M; ++i) {
		int u, v; cin >> u >> v;
		if (u == v) ++ans;
		else if (adj[u].find(v) == adj[u].end()) {
			adj[u].insert(v);
			adj[v].insert(u);
		} else {
			++ans;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}