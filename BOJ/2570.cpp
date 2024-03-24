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
	int N, M; cin >> N >> M;
	vector<vector<int>> chess(N, vector<int>(N, 0)), rchess(N, vector<int>(N)), lchess(N, vector<int>(N));
	for (int i = 0; i < M; ++i) {
		int y, x; cin >> y >> x; --y; --x;
		chess[y][x] = 1;
	}
	int n = -1, m = -1;
	for (int i = 0; i < N; ++i) {
		int y = 0, x = i;
		++n;
		while (0 <= y && y < N && 0 <= x && x < N) {
			if (chess[y][x] == 1) {
				++n; ++y; ++x; continue;
			}
			rchess[y][x] = n;
			++y; ++x;
		}
	}
	for (int i = 1; i < N; ++i) {
		int y = i, x = 0;
		++n;
		while (0 <= y && y < N && 0 <= x && x < N) {
			if (chess[y][x] == 1) {
				++n; ++y; ++x; continue;
			}
			rchess[y][x] = n;
			++y; ++x;
		}
	}
	for (int i = 0; i < N; ++i) {
		int y = 0, x = i;
		++m;
		while (0 <= y && y < N && 0 <= x && x < N) {
			if (chess[y][x] == 1) {
				++m; ++y; --x; continue;
			}
			lchess[y][x] = m;
			++y; --x;
		}
	}
	for (int i = 1; i < N; ++i) {
		int y = i, x = N - 1;
		++m;
		while (0 <= y && y < N && 0 <= x && x < N) {
			if (chess[y][x] == 1) {
				++m; ++y; --x; continue;
			}
			lchess[y][x] = m;
			++y; --x;
		}
	}
	++n; ++m;
	// 0 ~ n - 1, 0 ~ m - 1
	vector<vector<int>> adj(n);
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (chess[i][j] == 0) {
		adj[rchess[i][j]].push_back(lchess[i][j]);
	}
	int ans = bipartiteMatch(n, m, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}