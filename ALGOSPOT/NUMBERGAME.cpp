#include <bits/stdc++.h>
using namespace std;

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];

int play(int left, int right) {
	if (left > right) return 0;
	int& ret = cache[left][right];
	if (ret != -1) return ret;
	ret = max(board[left] - play(left + 1, right), board[right] - play(left, right - 1));
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;
}

void solve() {
	cin >> n; for (int i = 0; i < n; ++i) cin >> board[i];
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cache[i][j] = -1;
	cout << play(0, n - 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}