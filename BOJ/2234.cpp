#include <bits/stdc++.h>
using namespace std;

int N, M;
int castle[50][50];
int room[50][50];

int dy[4] = {0, -1, 0, 1}, dx[4] = {-1, 0, 1, 0};

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) cin >> castle[i][j];
	int idx = 0;
	memset(room, -1, sizeof(room));
	for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
		if (room[i][j] != -1) continue;
		queue<int> Q; Q.push(i * N + j); room[i][j] = ++idx;
		while (!Q.empty()) {
			int here = Q.front(); Q.pop();
			int y = here / N, x = here % N;
			for (int k = 0; k < 4; ++k) {
				int ny = y + dy[k], nx = x + dx[k];
				if (!((castle[y][x] >> k) & 1) && room[ny][nx] == -1) {
					room[ny][nx] = idx;
					Q.push(ny * N + nx);
				}
			}
		}
	}
	cout << idx << '\n';
	int cnt[idx + 1]; memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) ++cnt[room[i][j]];
	cout << *max_element(cnt, cnt + idx + 1) << '\n';
	int ans = *max_element(cnt, cnt + idx + 1);
	for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < M && 0 <= nj && nj < N && room[i][j] != room[ni][nj]) {
				ans = max(ans, cnt[room[i][j]] + cnt[room[ni][nj]]);
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}