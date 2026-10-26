#include <bits/stdc++.h>
using namespace std;
int n, m;
int dx[8] = {1, -1, 0, 0, -1, -1, 1, 1}, dy[8] = {0, 0, 1, -1, -1, 1, -1, 1};

struct Point {
	int y, x, d;
};

bool available(int y, int x) {
	if (0 <= y && y < n && 0 <= x && x < m) return true;
	return false;
}

void dfs(int y, int x, vector<vector<bool>>& reachable, vector<vector<int>>& dis, vector<vector<int>>& map, int l) {
	reachable[y][x] = 1;
	for (int i = 0; i < 4; ++i) {
		int ny = y + dy[i], nx = x + dx[i];
		if (available(ny, nx) && dis[ny][nx] >= l && map[ny][nx] != 1 && !reachable[ny][nx]) dfs(ny, nx, reachable, dis, map, l);
	}
}

bool roundTrip(int y, int x, int l, vector<vector<int>>& dis, vector<vector<int>>& map) {
	if (dis[y][x] < l) return false;
	vector<vector<bool>> reachable(n, vector<bool>(m));
	dfs(y, x, reachable, dis, map, l);
	bool visited[n][m]; memset(visited, 0, sizeof(visited));
	deque<Point> V;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (map[i][j] == 1) {
		V.push_back({i, j, 0});
		visited[i][j] = 1;
	}
	while (!V.empty()) {
		Point p = V.front(); V.pop_front();
		for (int i = 0; i < 8; ++i) {
			int ny = p.y + dy[i], nx = p.x + dx[i];
			if (available(ny, nx) && !reachable[ny][nx] && !visited[ny][nx]) {
				visited[ny][nx] = 1;
				V.push_back({ny, nx, 0});
			}
		}
	}
	if (visited[y][x]) return false;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if ((i == 0 || i == n - 1 || j == 0 || j == m - 1) && visited[i][j]) return false;
	return true;
}

void solve() {
	int q; cin >> n >> m >> q;
	vector<vector<int>> dis(n, vector<int>(m, -1)), map(n, vector<int>(m));
	deque<Point> V;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		char t; cin >> t;
		if (t == '.') map[i][j] = 0;
		if (t == '#') map[i][j] = 1;
		if (t == 'v') {
			map[i][j] = 2;
			dis[i][j] = 0;
			V.push_back({i, j, 0});
		}
	}
	while (!V.empty()) {
		Point p = V.front(); V.pop_front();
		for (int i = 0; i < 4; ++i) {
			int ny = p.y + dy[i], nx = p.x + dx[i], nd = p.d + 1;
			if (available(ny, nx) && dis[ny][nx] == -1) {
				dis[ny][nx] = nd;
				V.push_back({ny, nx, nd});
			}
		}
	}
	while (q--) {
		int y, x; cin >> y >> x; --y; --x;
		int l = 0, r = n + m, mid;
		while (l < r) {
			mid = (l + r + 1) / 2;
			if (roundTrip(y, x, mid, dis, map)) l = mid;
			else r = mid - 1;
		}
		cout << l << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}