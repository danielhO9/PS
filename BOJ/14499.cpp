#include <bits/stdc++.h>
using namespace std;

int N, M, x, y, K;
int arr[20][20];
int val[7], sur[7];

int dy[4] = {0, 0, -1, 1};
int dx[4] = {1, -1, 0, 0};

void query(int type) {
	if (type == 1) {
		int tmp = sur[6];
		sur[6] = sur[3];
		sur[3] = sur[1];
		sur[1] = sur[4];
		sur[4] = tmp;
	}
	if (type == 2) {
		int tmp = sur[6];
		sur[6] = sur[4];
		sur[4] = sur[1];
		sur[1] = sur[3];
		sur[3] = tmp;
	}
	if (type == 3) {
		int tmp = sur[2];
		sur[2] = sur[1];
		sur[1] = sur[5];
		sur[5] = sur[6];
		sur[6] = tmp;
	}
	if (type == 4) {
		int tmp = sur[6];
		sur[6] = sur[5];
		sur[5] = sur[1];
		sur[1] = sur[2];
		sur[2] = tmp;
	}
}

void solve() {
	cin >> N >> M >> y >> x >> K;
	memset(val, 0, sizeof(val));
	for (int i = 0; i < 7; ++i) sur[i] = i;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> arr[i][j];
	while (K--) {
		int way; cin >> way;
		int ny = y + dy[way - 1], nx = x + dx[way - 1];
		if (0 <= ny && ny < N && 0 <= nx && nx < M) {
			query(way);
			y += dy[way - 1]; x += dx[way - 1];
			cout << val[sur[1]] << '\n';
			if (arr[y][x] == 0) {
				arr[y][x] = val[sur[6]];
			} else {
				val[sur[6]] = arr[y][x];
				arr[y][x] = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}