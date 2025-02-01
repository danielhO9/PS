#include <bits/stdc++.h>
using namespace std;

int r, c, d;
char maze[11][11];
int dis[121][121];
const int MAX = 987654321;
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void solve() {
	cin >> r >> c >> d;
	for (int i = 0; i < r; ++i) {
		string s; cin >> s;
		for (int j = 0; j < c; ++j) maze[i][j] = s[j];
	}
	for (int i = 0; i < r * c; ++i) for (int j = 0; j < r * c; ++j) dis[i][j] = MAX;
	unordered_map<int, int> ord;
	for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (maze[i][j] != '#') {
		int here = i * c + j;
		if (maze[i][j] == 'S') ord[0] = here;
		if ('1' <= maze[i][j] && maze[i][j] <= '9') ord[maze[i][j] - '0'] = here;
		if (maze[i][j] == 'E') ord[d + 1] = here;
		dis[here][here] = 0;
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < r && 0 <= nj && nj < c && maze[ni][nj] != '#') {
				int there = ni * c + nj;
				dis[here][there] = 1;
			}
		}
	}
	for (int m = 0; m < r * c; ++m) for (int i = 0; i < r * c; ++i) for (int j = 0; j < r * c; ++j) {
		dis[i][j] = min(dis[i][j], dis[i][m] + dis[m][j]);
	}
	int ans = 0;
	for (int i = 0; i <= d; ++i) ans += dis[ord[i]][ord[i + 1]];
	cout << ans << '\n';


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}