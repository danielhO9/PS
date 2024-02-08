#include <bits/stdc++.h>
using namespace std;

int N, M, m[8][8], ans, visited[8][8], dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
vector<int> wall;

void dfs(int y, int x) {
	int ny, nx;
	for (int i = 0; i < 4; ++i) {
		ny = y + dy[i]; nx = x + dx[i];
		if (0 <= ny && ny < N && 0 <= nx && nx < M && visited[ny][nx] == 0) {
			visited[ny][nx] = 2; dfs(ny, nx);
		}
	}
}

int safeArea() {
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (m[i][j] == 1) visited[i][j] = 1;
	for (auto i: wall) visited[i / M][i % M] = 1;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (m[i][j] == 2 && visited[i][j] == 0) {
		visited[i][j] = 2; dfs(i, j);
	}
	int temp = 0;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (visited[i][j] == 0) ++temp;
	return temp;
}

void solution() {
	if (wall.size() == 3) {
		ans = max(ans, safeArea());
		return;
	}
	if (wall.empty()) {
		for (int i = 0; i <= N * M - 1; ++i) if (m[i / M][i % M] == 0) {
			wall.push_back(i);
			solution();
			wall.pop_back();
		}
		return;
	}
	for (int i = wall.back() + 1; i <= N * M - 1; ++i) if (m[i / M][i % M] == 0) {
		wall.push_back(i);
		solution();
		wall.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> m[i][j];
	solution();
	cout << ans;
}