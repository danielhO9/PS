#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, m; cin >> n >> m;
	int ans[n][m];
	int t = min(m, n + 1);
	if (t == 1) cout << 0 << '\n';
	else cout << t << '\n';
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (i == 0) ans[i][j] = j;
		else if (i <= t - 2) {
			if (j < t) {
				ans[i][j] = ans[i - 1][(j + 1) % t];
			} else {
				ans[i][j] = j;
			}
		} else {
			ans[i][j] = j;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}