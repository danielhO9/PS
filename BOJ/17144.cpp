#include <bits/stdc++.h>
using namespace std;

int R, C, T, room[50][50][1001], dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1}, u, d;

void spend(int t) {
	int cnt;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) if (room[i][j][t - 1] != -1) {
		cnt = 0;
		for (int k = 0; k < 4; ++k) if (0 <= i + dy[k] && i + dy[k] < R && 0 <= j + dx[k] && j + dx[k] < C) {
			if (room[i + dy[k]][j + dx[k]][t - 1] != -1) { ++cnt; room[i + dy[k]][j + dx[k]][t] += room[i][j][t - 1] / 5; }
		}
		room[i][j][t] += room[i][j][t - 1];
		room[i][j][t] -= (room[i][j][t - 1] / 5) * cnt;
	}
	room[u][0][t] = -1; room[d][0][t] = -1;
	for (int i = u - 1; i >= 1; --i) room[i][0][t] = room[i - 1][0][t];
	for (int i = 0; i < C - 1; ++i) room[0][i][t] = room[0][i + 1][t];
	for (int i = 0; i <= u - 1; ++i) room[i][C - 1][t] = room[i + 1][C - 1][t];
	for (int i = C - 1; i >= 1; --i) room[u][i][t] = room[u][i - 1][t];
	room[u][1][t] = 0;
	for (int i = d + 1; i <= R - 2; ++i) room[i][0][t] = room[i + 1][0][t];
	for (int i = 0; i < C - 1; ++i) room[R - 1][i][t] = room[R - 1][i + 1][t];
	for (int i = R - 1; i > d; --i) room[i][C - 1][t] = room[i - 1][C - 1][t];
	for (int i = C - 1; i >= 1; --i) room[d][i][t] = room[d][i - 1][t];
	room[d][1][t] = 0;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> R >> C >> T;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		cin >> room[i][j][0];
		if (room[i][j][0] == -1 && u == 0) u = i;
		else if (room[i][j][0] == -1) d = i;
	}
	for (int i = 1; i <= T; ++i) spend(i);
	// for (int i = 0; i < R; ++i) { for (int j = 0; j < C; ++j) cout << room[i][j][T] << " "; cout << "\n"; }
	int ans = 0;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) ans += room[i][j][T];
	cout << ans + 2;
}