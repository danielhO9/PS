#include <bits/stdc++.h>
using namespace std;

int H, W;
bool wall[100][100];
int dis[100][100];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

void solve() {
	cin >> W >> H;
	vector<pair<int, int>> p;
	memset(wall, false, sizeof(wall));
	for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) {
		char tmp; cin >> tmp;
		if (tmp == 'C') p.push_back({i, j});
		else if (tmp == '*') wall[i][j] = true;
	}
	memset(dis, -1, sizeof(dis));
	queue<pair<int, int>> Q; Q.push(p[0]); dis[p[0].first][p[0].second] = 0;
	while (!Q.empty()) {
		auto here = Q.front(); Q.pop();
		for (int i = 0; i < 4; ++i) {
			int ny = here.first + dy[i], nx = here.second + dx[i];
			while (0 <= ny && ny < H && 0 <= nx && nx < W && !wall[ny][nx]) {
				if (dis[ny][nx] == -1) {
					dis[ny][nx] =  dis[here.first][here.second] + 1;
					Q.push({ny, nx});
				}
				ny += dy[i]; nx += dx[i];
			}
		}
	}
	cout << dis[p[1].first][p[1].second] - 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}