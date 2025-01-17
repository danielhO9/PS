#include <bits/stdc++.h>
using namespace std;

int N, M;
int dis[500][500];
char board[500][500];
int deg[500][500];
const int MAX = 987654321;

int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> board[i][j];
	memset(dis, -1, sizeof(dis));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) deg[i][j] = 2;
	queue<pair<int, int>> q;
	int sy, sx;

	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (board[i][j] == 'G') {
			dis[i][j] = 0;
			deg[i][j] = 0;
		}
		if (board[i][j] == '#') {
			deg[i][j] = 0;
		}
		if (board[i][j] == 'S') { sy = i; sx = j; }
	}
	
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (board[i][j] == 'G') {
			for (int k = 0; k < 4; ++k) {
				int ni = i + dy[k], nj = j + dx[k];
				if (0 <= ni && ni < N && 0 <= nj && nj < M) --deg[ni][nj];
				if (dis[ni][nj] == -1 && deg[ni][nj] == 0) q.push({ni, nj});
			}
		}
	}

	while (!q.empty()) {
		int y = q.front().first, x = q.front().second; q.pop();
		int f = MAX, s = MAX;
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < M && dis[ny][nx] != -1) {
				if (f >= dis[ny][nx] + 1) {
					s = f;
					f = dis[ny][nx] + 1;
				} else if (s >= dis[ny][nx] + 1) {
					s = dis[ny][nx] + 1;
				}
			}
		}
		dis[y][x] = s;
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < M && dis[ny][nx] == -1) {
				--deg[ny][nx];
				if (deg[ny][nx] == 0) {
					q.push({ny, nx});
				}
			}
		}
		
	}
	
	// for (int i = 0; i < N; ++i) {
	// 	for (int j = 0; j < M; ++j) cout << dis[i][j] << ' ';
	// 	cout << "\n";
	// }
	cout << dis[sy][sx];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}