#include <bits/stdc++.h>
using namespace std;

int N;
bool board[50][50];
bool visited[50][50];
int dist[50][50];

int dy[6] = {-1, -1, 0, 0, 1, 1}, dx[6] = {0, 1, -1, 1, -1, 0};

void solve() {
	cin >> N;
	bool flag = true;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		char tmp; cin >> tmp;
		if (tmp == '-') board[i][j] = false;
		else {
			board[i][j] = true;
			flag = false;
		}
	}
	if (flag) {
		cout << 0;
		return;
	}
	flag = true;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (board[i][j]) {
		for (int k = 0; k < 6; ++k) {
			int ny = i + dy[k], nx = j + dx[k];
			if (0 <= ny && ny < N && 0 <= nx && nx < N && board[ny][nx]) flag = false;
		}
	}
	if (flag) {
		cout << 1;
		return;
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (board[i][j]) {
		memset(dist, 0, sizeof(dist));
		dist[i][j] = 1;
		queue<pair<pair<int, int>, int>> Q; Q.push({{i, j}, 0});
		while (!Q.empty()) {
			auto [there, dis] = Q.front(); Q.pop();
			for (int k = 0; k < 6; ++k) {
				int ni = there.first + dy[k], nj = there.second + dx[k], ndis = (dis + 1) % 2;
				if (0 <= ni && ni < N && 0 <= nj && nj < N && board[ni][nj]) {
					if (!((dist[ni][nj] >> ndis) & 1)) {
						dist[ni][nj] ^= (1 << ndis);
						Q.push({{ni, nj}, ndis});
						if (dist[ni][nj] == 3) {
							cout << 3;
							return;
						}
					}
				}
			}
		}
	}
	cout << 2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}