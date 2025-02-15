#include <bits/stdc++.h>
using namespace std;

int n;
int board[50][50];
int dis[50][50];
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		for (int j = 0; j < n; ++j) board[i][j] = s[j] - '0';
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dis[i][j] = INT32_MAX;
	dis[n - 1][n - 1] = 0;
	deque<pair<int, int>> dq; dq.push_back({n - 1, n - 1});
	while (!dq.empty()) {
		auto [y, x] = dq.front(); dq.pop_front();
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < n && 0 <= nx && nx < n && dis[ny][nx] == INT32_MAX) {
				if (board[ny][nx]) dq.push_front({ny, nx});
				else dq.push_back({ny, nx});
				dis[ny][nx] = dis[y][x] + (1 - board[ny][nx]);
			}
		}
	}
	cout << dis[0][0];
}