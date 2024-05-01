#include <bits/stdc++.h>
using namespace std;

int N, M;
int arr[100][100];
int changed;

void query(int type) {
	if (type == 1) {
		for (int i = 0; i < N / 2; ++i) for (int j = 0; j < M; ++j) swap(arr[i][j], arr[N - 1 - i][j]);
	}
	if (type == 2) {
		for (int i = 0; i < N; ++i) for (int j = 0; j < M / 2; ++j) swap(arr[i][j], arr[i][M - 1 - j]);
	}
	if (type == 3) {
		int tarr[N][M]; for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) tarr[i][j] = arr[i][j];
		for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) arr[j][N - 1 - i] = tarr[i][j];
		swap(N, M);
	}
	if (type == 4) {
		int tarr[N][M]; for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) tarr[i][j] = arr[i][j];
		for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) arr[M - 1 - j][i] = tarr[i][j];
		swap(N, M);
	}
	if (type == 5) {
		int tarr[N][M]; for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) tarr[i][j] = arr[i][j];
		for (int i = 0; i < N / 2; ++i) for (int j = 0; j < M / 2; ++j) arr[i][j + M / 2] = tarr[i][j];
		for (int i = 0; i < N / 2; ++i) for (int j = M / 2; j < M; ++j) arr[i + N / 2][j] = tarr[i][j];
		for (int i = N / 2; i < N; ++i) for (int j = 0; j < M / 2; ++j) arr[i - N / 2][j] = tarr[i][j];
		for (int i = N / 2; i < N; ++i) for (int j = M / 2; j < M; ++j) arr[i][j - M / 2] = tarr[i][j];
	}
	if (type == 6) {
		int tarr[N][M]; for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) tarr[i][j] = arr[i][j];
		for (int i = 0; i < N / 2; ++i) for (int j = 0; j < M / 2; ++j) arr[i + N / 2][j] = tarr[i][j];
		for (int i = 0; i < N / 2; ++i) for (int j = M / 2; j < M; ++j) arr[i][j - M / 2] = tarr[i][j];
		for (int i = N / 2; i < N; ++i) for (int j = 0; j < M / 2; ++j) arr[i][j + M / 2] = tarr[i][j];
		for (int i = N / 2; i < N; ++i) for (int j = M / 2; j < M; ++j) arr[i - N / 2][j] = tarr[i][j];
	}
}

void solve() {
	changed = 0;
	int R; cin >> N >> M >> R;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> arr[i][j];
	for (int i = 0; i < R; ++i) {
		int type; cin >> type;
		query(type);
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) cout << arr[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}