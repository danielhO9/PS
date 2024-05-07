#include <bits/stdc++.h>
using namespace std;

int N, M;
int board[20][20];
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
int cnt = 0, ans = 11;
vector<pair<int, int>> coin;

void dfs() {
	if (cnt == 10) return;
	for (int i = 0; i < 4; ++i) {
		++cnt;
		for (int j = 0; j < 2; ++j) {
			coin[j].first += dy[i];
			coin[j].second += dx[i];
		}
		int tmp = 0;
		bool moved[2] = {true, true};
		for (int j = 0; j < 2; ++j) if (0 <= coin[j].first && coin[j].first < N && 0 <= coin[j].second && coin[j].second < M) {
			++tmp;
			if (board[coin[j].first][coin[j].second] == 1) {
				coin[j].first -= dy[i];
				coin[j].second -= dx[i];
				moved[j] = false;
			}
		}
		if (tmp == 1) ans = min(ans, cnt);
		else if (tmp == 2) dfs();

		for (int j = 0; j < 2; ++j) if (moved[j]) {
			coin[j].first -= dy[i];
			coin[j].second -= dx[i];
		}
		--cnt;
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		char tmp; cin >> tmp;
		if (tmp == 'o') {
			coin.push_back({i, j});
			board[i][j] = 0;
		}
		else if (tmp == '.') board[i][j] = 0;
		else board[i][j] = 1;
	}
	dfs();
	if (ans == 11) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}