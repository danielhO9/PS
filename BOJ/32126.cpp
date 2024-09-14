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

// time complexity: V*E
void solve() {
	int N, K; cin >> N >> K;
	int MAX_N = K, MAX_M = N;
	vector<vector<int>> adj(MAX_N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			int tmp; cin >> tmp;
			if (tmp) adj[j].push_back(i);
		}
	}
	aMatch = vector<int>(MAX_N, -1);
	bMatch = vector<int>(MAX_M, -1);
	int left = 0;
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = MAX_N - 1; start >= 0; --start) {
		if (dfs(start, visited, adj)) {
			++left;
		} else {
			if (left) {
				--left;
				++size;
			}
		}
		for (int i = 0; i < MAX_N; ++i) visited[i] = false;
	}
	cout << size + left / 2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}