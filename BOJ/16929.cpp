#include <bits/stdc++.h>
using namespace std;

int N, M;
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};
vector<int> adj[2500];
bool visited[2500];
bool exist = false;

void dfs(int v, int p) {
	visited[v] = true;
	for (auto u: adj[v]) if (u != p) {
		if (visited[u]) {
			exist = true;
			return;
		}
		dfs(u, v);
	}
}

void solve() {
	cin >> N >> M;
	int board[N][M];
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		char tmp; cin >> tmp;
		board[i][j] = tmp - 'A';
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < N && 0 <= nj && nj < M && board[i][j] == board[ni][nj]) {
				adj[i * M + j].push_back(ni * M + nj);
			}
		}
	}
	for (int i = 0; i < N * M; ++i) if (!visited[i]) dfs(i, -1);
	if (exist) cout << "Yes";
	else cout << "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}