#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> b(m); for (int i = 0; i < m; ++i) cin >> b[i];
	vector<int> v(30);
	vector<int> pos(30);
	for (int i = 0; i < n; ++i) for (int j = 0; j < 30; ++j) {
		if ((a[i] >> j) & 1) v[j] ^= 1;
	}
	int ans[2] = {0, 0};
	for (int i = 0; i < 30; ++i) if (v[i] == 1) ans[0] += (1 << i);
	for (int i = 0; i < m; ++i) for (int j = 0; j < 30; ++j) {
		if ((b[i] >> j) & 1) pos[j] |= 1;
	}
	for (int i = 0; i < 30; ++i) {
		if (pos[i] == 1) {
			if (n % 2 == 0) v[i] = 0;
			else v[i] = 1;
		}
		if (v[i] == 1) ans[1] += (1 << i);
	}
	sort(ans, ans + 2);
	cout << ans[0] << ' ' << ans[1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}