#include <bits/stdc++.h>
using namespace std;

int N, M, r, c, d;
int room[50][50];
int ans = 0;

int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

void query() {
	if (room[r][c] == 0) {
		++ans; room[r][c] = 2;
	}
	int flag = false;
	for (int i = 0; i < 4; ++i) {
		int ny = r + dy[i], nx = c + dx[i];
		if (0 <= ny && ny < N && 0 <= nx && nx < M && room[ny][nx] == 0) flag = true;
	}
	if (flag) {
		d = (d + 3) % 4;
		int ny = r + dy[d], nx = c + dx[d];
		if (0 <= ny && ny < N && 0 <= nx && nx < M && room[ny][nx] == 0) {
			r = ny, c = nx;
		}
		query();
	} else {
		int nd = d >= 2 ? d - 2 : d + 2;
		int ny = r + dy[nd], nx = c + dx[nd];
		if (0 <= ny && ny < N && 0 <= nx && nx < M && room[ny][nx] != 1) {
			r = ny, c = nx;
			query();
			return;
		} else {
			return;
		}
	}
}

void solve() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> room[i][j];
	query();
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}