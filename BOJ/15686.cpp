#include <bits/stdc++.h>
using namespace std;

struct dist {
	int y, x, d;
};

int N, M, city[50][50], ans, dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
vector<pair<int, int>> chicken;
vector<int> picked;
deque<dist> Q;
int visited[50][50];

int bfs() {
	int ret = 0;
	memset(visited, 0, sizeof(visited));
	for (auto i: picked) {
		Q.push_back({chicken[i].first, chicken[i].second, 0});
		visited[chicken[i].first][chicken[i].second] = 1;
	}
	int y, x, d;
	while (!Q.empty()) {
		for (int i = 0; i < 4; ++i) {
			y = Q.front().y + dy[i]; x = Q.front().x + dx[i]; d = Q.front().d;
			if (0 <= y && y < N && 0 <= x && x < N && !visited[y][x]) {
				Q.push_back({y, x, d + 1});
				if (city[y][x] == 1) ret += d + 1;
				visited[y][x] = 1;
			}
		}
		Q.pop_front();
	}
	return ret;
}

void solution() {
	if (picked.size() == M) return;
	if (picked.empty()) {
		for (int i = 0; i < chicken.size(); ++i) {
			picked.push_back({i});
			ans = min(ans, bfs());
			solution();
			picked.pop_back();
		}
		return;
	}
	for (int i = picked.back() + 1; i < chicken.size(); ++i) {
		picked.push_back({i});
		ans = min(ans, bfs());
		solution();
		picked.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		cin >> city[i][j];
		if (city[i][j] == 2) chicken.push_back({i, j});
	}
	ans = INT32_MAX;
	solution(); cout << ans;
}