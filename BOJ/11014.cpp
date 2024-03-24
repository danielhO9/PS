#include <bits/stdc++.h>
using namespace std;

int dx[6] = {-1, -1, -1, 1, 1, 1};
int dy[6] = {-1, 0, 1, -1, 0, 1};

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
	vector<vector<char>> room(N, vector<char>(M));
	int cnt = 0;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		cin >> room[i][j];
		if (room[i][j] == '.') ++cnt;
	}
	int n, m; n = ((M + 1) / 2) * N, m = (M / 2) * N;
	// 0 ~ n - 1, 0 ~ m - 1
	vector<vector<int>> adj(n);
	for (int i = 0; i < (M + 1) / 2; ++i) {
		int x = i * 2;
		for (int y = 0; y < N; ++y) {
			if (room[y][x] == 'x') continue;
			int num = i * N + y;
			for (int k = 0; k < 6; ++k) {
				int nx = x + dx[k], ny = y + dy[k];
				if (0 <= nx && nx < M && 0 <= ny && ny < N && room[ny][nx] == '.') {
					int nnum = (nx - 1) / 2 * N + ny;
					adj[num].push_back(nnum);
				}
			}
		}
	}
	int ans = bipartiteMatch(n, m, adj);
	cout << cnt - ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}