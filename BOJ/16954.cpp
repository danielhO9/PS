#include <bits/stdc++.h>
using namespace std;

int wall[8][8];
bool vis[8][8][100];
int dy[9] = {-1, -1, -1, 0, 0, 1, 1, 1, 0}, dx[9] = {-1, 0, 1, -1, 1, -1, 0, 1, 0};

void solve() {
	for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) {
		char tmp; cin >> tmp;
		wall[i][j] = (tmp == '#');
	}
	memset(vis, 0, sizeof(vis)); vis[7][0][0] = true;
	queue<pair<pair<int, int>, int>> Q; Q.push({{7, 0}, 0});
	int time = 0;
	while (!Q.empty()) {
		auto here = Q.front().first;
		int t = Q.front().second; Q.pop();
		if (t != time) {
			++time;
			for (int i = 6; i >= 0; --i) for (int j = 0; j < 8; ++j) wall[i + 1][j] = wall[i][j];
			for (int i = 0; i < 8; ++i) wall[0][i] = 0;
		}
		if (wall[here.first][here.second]) continue;
		for (int i = 0; i < 9; ++i) {
			int ny = here.first + dy[i], nx = here.second + dx[i];
			if (0 <= ny && ny < 8 && 0 <= nx && nx < 8 && !wall[ny][nx] && t < 100 && !vis[ny][nx][t + 1]) {
				Q.push({{ny, nx}, t + 1});
				vis[ny][nx][t + 1] = true;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 100; ++i) ans |= vis[0][7][i];
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}