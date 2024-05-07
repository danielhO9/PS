#include <bits/stdc++.h>
using namespace std;

int N;
int arr[1 << 7][1 << 7], tmp[1 << 7][1 << 7];

void query(int k, int sz) {
	for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) tmp[i][j] = arr[i][j];
	if (k == 1) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			if ((i - y) * 2 < (1 << sz)) swap(arr[i][j], arr[(1 << sz) - 1 - (i - y) + y][j]);
		}
	}
	else if (k == 2) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			if ((j - x) * 2 < (1 << sz)) swap(arr[i][j], arr[i][(1 << sz) - 1 - (j - x) + x]);
		}
	}
	else if (k == 3) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			arr[y + j - x][x + (1 << sz) - 1 - (i - y)] = tmp[i][j];
		}
	}
	else if (k == 4) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			arr[y + (1 << sz) - 1 - (j - x)][x + i - y] = tmp[i][j];
		}
	}
	else if (k == 5) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			if ((i  / (1 << sz)) * 2 < (1 << (N - sz))) swap(arr[i][j], arr[((1 << (N - sz)) - 1 - (i  / (1 << sz))) * (1 << sz) + i - y][j]);
		}
	}
	else if (k == 6) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i  / (1 << sz)) * (1 << sz);
			int x = (j  / (1 << sz)) * (1 << sz);
			if ((j  / (1 << sz)) * 2 < (1 << (N - sz))) swap(arr[i][j], arr[i][((1 << (N - sz)) - 1 - (j  / (1 << sz))) * (1 << sz) + j - x]);
		}
	}
	else if (k == 7) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i / (1 << sz)) * (1 << sz);
			int x = (j / (1 << sz)) * (1 << sz);
			arr[(j / (1 << sz)) * (1 << sz) + i - y][((1 << (N - sz)) - 1 - (i / (1 << sz))) * (1 << sz) + j - x] = tmp[i][j];
		}
	}
	else if (k == 8) {
		for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) {
			int y = (i / (1 << sz)) * (1 << sz);
			int x = (j / (1 << sz)) * (1 << sz);
			arr[((1 << (N - sz)) - 1 - (j / (1 << sz))) * (1 << sz) + i - y][(i / (1 << sz)) * (1 << sz) + j - x] = tmp[i][j];
		}
	}
}

void solve() {
	int R; cin >> N >> R;
	for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < (1 << N); ++j) cin >> arr[i][j];
	while (R--) {
		int k, l; cin >> k >> l;
		query(k, l);
	}
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < (1 << N); ++j) cout << arr[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}