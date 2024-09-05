#include <bits/stdc++.h>
using namespace std;

vector<int> aMatch, bMatch;

bool dfs(int a, vector<bool>& visited, vector<vector<int>>& adj) {
	if (visited[a]) return false;
	visited[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b], visited, adj)) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch(int MAX_N, int MAX_M, vector<vector<int>>& adj) {
	aMatch = vector<int>(MAX_N, -1);
	bMatch = vector<int>(MAX_M, -1);
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = 0; start < MAX_N; ++start) {
		if (dfs(start, visited, adj)) {
			++size;
			for (int i = 0; i < MAX_N; ++i) visited[i] = false;
		}
	}
	return size;
}

// time complexity: V*E
void solve() {
	int MAX_N, MAX_M; cin >> MAX_N >> MAX_M;
	vector<int> s(MAX_N), k(MAX_M);
	for (int i = 0; i < MAX_N; ++i) cin >> s[i];
	for (int i = 0; i < MAX_M; ++i) cin >> k[i];
	vector<vector<int>> adj(MAX_N);
	for (int i = 0; i < MAX_N; ++i) for (int j = 0; j < MAX_M; ++j) {
		if ((s[i] <= k[j] * 2 && k[j] * 4 <= s[i] * 3) || (s[i] <= k[j] && k[j] * 4 <= s[i] * 5)) {
			adj[i].push_back(j);
		}
	}
	int ans = bipartiteMatch(MAX_N, MAX_M, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}