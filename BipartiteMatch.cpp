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

int bipartiteMatch(int& MAX_N, int& MAX_M, vector<vector<int>>& adj) {
	vector<int> aMatch = vector<int>(MAX_N, -1);
	vector<int> bMatch = vector<int>(MAX_M, -1);
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = 0; start < MAX_N; ++start) {
		if (dfs(start, aMatch, bMatch, visited, adj)) {
			++size;
			for (int i = 0; i < MAX_N; ++i) visited[i] = false;
		}
	}
	return size;
}

// time complexity: V*E
void solve() {
	int MAX_N, MAX_M;
	// 0 ~ MAX_N - 1, 0 ~ MAX_M - 1
	vector<vector<int>> adj(MAX_N);
	int ans = bipartiteMatch(MAX_N, MAX_M, adj);
	cout << ans;
}