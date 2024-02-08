#include <bits/stdc++.h>
using namespace std;

int N, M, cheese[100][100], deg[100][100], ans;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

bool available(int y, int x) {
	if (0 <= y && y < N && 0 <= x && x < M) return true;
	return false;
}

void dfs(int y, int x) {
	for (int i = 0; i < 4; ++i) if (available(y + dy[i], x + dx[i])) {
		if (cheese[y + dy[i]][x + dx[i]]) ++deg[y + dy[i]][x + dx[i]];
		else if (deg[y + dy[i]][x + dx[i]] == 0) {
			deg[y + dy[i]][x + dx[i]] = -1;
			dfs(y + dy[i], x + dx[i]);
		}
	}
}

bool done() {
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (cheese[i][j]) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> cheese[i][j];
	while (!done()) {
		memset(deg, 0, sizeof(deg));
		deg[0][0] = -1; dfs(0, 0);
		for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (deg[i][j] >= 2) cheese[i][j] = 0;
		++ans;
	}
	cout << ans;
}