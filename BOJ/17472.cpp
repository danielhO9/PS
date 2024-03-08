#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

int m[10][10];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void solve() {
	int N, M; cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> m[i][j];
	int cnt = 1;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (m[i][j] == 1) {
			++cnt;
			deque<pair<int, int>> Q; Q.push_back(make_pair(i, j)); m[i][j] = cnt;
			while (!Q.empty()) {
				int y = Q.front().first, x = Q.front().second; Q.pop_front();
				for (int k = 0; k < 4; ++k) {
					int ny = y + dy[k], nx = x + dx[k];
					if (0 <= ny && ny < N && 0 <= nx && nx < M && m[ny][nx] == 1) {
						Q.push_back(make_pair(ny, nx)); m[ny][nx] = cnt;
					}
				}
			}
		}
	}
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> Q;
	pair<int, int> near[N][M][4];
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < 4; ++k) near[i][j][k] = make_pair(-1, -1);
	for (int k = 0; k < 4; ++k) {
		for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (m[i][j] == 0) {
			int y = i, x = j, cnt = 0;
			while (0 <= y && y < N && 0 <= x && x < M && m[y][x] == 0) {
				y += dy[k]; x += dx[k]; ++cnt;
			}
			if (0 <= y && y < N && 0 <= x && x < M) near[i][j][k] = make_pair(m[y][x], cnt - 1);
		}
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (m[i][j] == 0) {
		if (near[i][j][0].first != -1 && near[i][j][1].first != -1) {
			Q.push({near[i][j][0].second + near[i][j][1].second + 1, {near[i][j][0].first, near[i][j][1].first}});
		}
		if (near[i][j][2].first != -1 && near[i][j][3].first != -1) {
			Q.push({near[i][j][2].second + near[i][j][3].second + 1, {near[i][j][2].first, near[i][j][3].first}});
		}
	}
	vector<int> parents(8);
	for (int i = 1; i <= 7; ++i) parents[i] = i;
	int ans = 0;
	while (!Q.empty()) {
		int dis = Q.top().first, a = Q.top().second.first, b = Q.top().second.second; Q.pop();
		if (dis <= 1) continue;
		if (find(parents, a) != find(parents, b)) {
			ans += dis;
			Union(parents, a, b);
		}
	}
	for (int i = 2; i <= cnt; ++i) if (find(parents, 2) != find(parents, i)) {
		cout << -1; return;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}