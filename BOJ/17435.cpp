#include <bits/stdc++.h>
using namespace std;

void solve() {
	int m; cin >> m;
	int f[20][m + 1]; memset(f, -1, sizeof(f));
	for (int i = 1; i <= m; ++i) cin >> f[0][i];
	for (int i = 1; i < 20; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
	int Q; cin >> Q;
	while (Q--) {
		int n, x; cin >> n >> x;
		for (int i = 0; i < 20; ++i) if ((n >> i) & 1) {
			x = f[i][x];
		}
		cout << x << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}