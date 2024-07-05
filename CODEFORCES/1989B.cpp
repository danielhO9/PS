#include <bits/stdc++.h>
using namespace std;

void solve() {
	string a, b; cin >> a >> b;
	int n  = a.size(), m = b.size();
	int ans = n + m;
	for (int i = 0; i < m; ++i) {
		int j = i;
		for (int k = 0; k < n; ++k) {
			if (j == m) break;
			if (a[k] == b[j]) ++j;
		}
		ans = min(ans, n + m - (j - i));
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}