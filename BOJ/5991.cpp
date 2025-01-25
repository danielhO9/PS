#include <bits/stdc++.h>
using namespace std;

int R, C;
int F[40][40];
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> R >> C;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> F[i][j];
	
	int ans = F[0][0]; F[0][0] = 0;
	int y = 0, x = 0;
	while (y != R - 1 || x != C - 1) {
		int mx = 0;
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < R && 0 <= nx && nx < C) {
				mx = max(mx, F[ny][nx]);
			}
		}
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < R && 0 <= nx && nx < C && F[ny][nx] == mx) {
				y = ny;
				x = nx;
				break;
			}
		}
		ans += F[y][x];
		F[y][x] = 0;
	}
	cout << ans;
}