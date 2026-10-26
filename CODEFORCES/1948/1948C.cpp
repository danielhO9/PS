#include <bits/stdc++.h>
using namespace std;

int cache[2][200000];
char grid[2][200000];

int matchCache(int y, int x) {
	if (x == 0) return 1;
	if (x == 1) {
		if (grid[1][0] == '>') return 1;
		else return 0;
	}
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	if (grid[y][x - 1] == '>' && (matchCache(y, x - 2) || matchCache(1 - y, x - 1))) ret = 1;
	else ret = 0;
	return ret;
}

void solve() {
	int n; cin >> n;
	for (int i = 0; i < 2; ++i) for (int j = 0; j < n; ++j) cin >> grid[i][j];
	for (int i = 0; i < 2; ++i) for (int j = 0; j < n; ++j) cache[i][j] = -1;
	int ans = matchCache(1, n - 1);
	if (ans == 1) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}