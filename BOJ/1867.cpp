#include <bits/stdc++.h>
using namespace std;

bool dfs(int a, vector<int>& aMatch, vector<int>& bMatch, vector<bool>& visited, vector<vector<int>>& adj) {
	if (visited[a]) return false;
	visited[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b], aMatch, bMatch, visited, adj)) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch(int& n, int& m, vector<vector<int>>& adj) {
	vector<int> aMatch = vector<int>(n, -1);
	vector<int> bMatch = vector<int>(m, -1);
	int size = 0;
	vector<bool> visited(n, false);
	for (int start = 0; start < n; ++start) {
		if (dfs(start, aMatch, bMatch, visited, adj)) {
			++size;
			for (int i = 0; i < n; ++i) visited[i] = false;
		}
	}
	return size;
}

void solve() {
	int n, m, k; cin >> n >> k; m = n;
	// 0 ~ n - 1, 0 ~ m - 1
	vector<vector<int>> adj(n);
	for (int i = 0; i < k; ++i) {
		int a, b; cin >> a >> b; --a; --b;
		adj[a].push_back(b);
	}
	int ans = bipartiteMatch(n, m, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}