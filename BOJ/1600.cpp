#include <bits/stdc++.h>
using namespace std;

int H, W, K;
bool wall[200][200];
int dis[200][200][31];

int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};
int jy[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, jx[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void solve() {
	cin >> K;
	cin >> W >> H;
	for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) cin >> wall[i][j];
	memset(dis, -1, sizeof(dis));
	queue<pair<int, int>> Q; Q.push({0, 0}); dis[0][0][0] = 0;
	while (!Q.empty()) {
		int here = Q.front().first, k = Q.front().second; Q.pop();
		int y = here / W, x = here % W;
		if (k < K) {
			for (int i = 0; i < 8; ++i) {
				int ny = y + jy[i], nx = x + jx[i];
				if (0 <= ny && ny < H && 0 <= nx && nx < W && !wall[ny][nx] && dis[ny][nx][k + 1] == -1) {
					Q.push({ny * W + nx, k + 1});
					dis[ny][nx][k + 1] = dis[y][x][k] + 1;
				}
			}
		}
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < H && 0 <= nx && nx < W && !wall[ny][nx] && dis[ny][nx][k] == -1) {
				Q.push({ny * W + nx, k});
				dis[ny][nx][k] = dis[y][x][k] + 1;
			}
		}
	}
	vector<int> ans;
	for (int i = 0; i <= K; ++i) if (dis[H - 1][W - 1][i] != -1) ans.push_back(dis[H - 1][W - 1][i]);
	if (ans.empty()) cout << -1;
	else cout << *min_element(ans.begin(), ans.end());
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}