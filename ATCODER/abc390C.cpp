#include <bits/stdc++.h>
using namespace std;

int H, W;
char board[1000][1000];

void solve() {
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		string s; cin >> s;
		for (int j = 0; j < W; ++j) board[i][j] = s[j];
	}
	int xmn = 1000, xmx = -1, ymn = 1000, ymx = -1;
	for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (board[i][j] == '#') {
		xmn = min(xmn, j);
		xmx = max(xmx, j);
		ymn = min(ymn, i);
		ymx = max(ymx, i);
	}
	if (xmn == 1000) {
		for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) if (board[i][j] == '?') {
			cout << "Yes";
			return;
		}
		cout << "No";
		return;
	}
	for (int i = ymn; i <= ymx; ++i) for (int j = xmn; j <= xmx; ++j) {
		if (board[i][j] == '.') {
			cout << "No";
			return;
		}
	}
	cout << "Yes";
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}