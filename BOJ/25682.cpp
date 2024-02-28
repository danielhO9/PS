#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, M, K; cin >> N >> M >> K;
	int board[N + 1][M + 1]; memset(board, 0, sizeof(board));
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
		char c; cin >> c;
		if (c == 'B') board[i][j] = 1;
		else board[i][j] = 0;
	}
	int sum[N + 1][M + 1]; memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
		int t = (i + j) % 2 == board[i][j];
		sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + t;
	}
	int ans = N * M;
	for (int i = 1; i <= N - K + 1; ++i) for (int j = 1; j <= M - K + 1; ++j) {
		int t = sum[i + K - 1][j + K - 1] - sum[i - 1][j + K - 1] - sum[i + K - 1][j - 1] + sum[i - 1][j - 1];
		t = min(t, K * K - t);
		ans = min(ans, t);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}