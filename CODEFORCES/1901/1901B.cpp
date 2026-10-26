#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	LL c[n]; for (int i = 0; i < n; ++i) cin >> c[i];
	LL ans = c[0] - 1;
	for (int i = 1; i < n; ++i) {
		if (c[i - 1] < c[i]) ans += c[i] - c[i - 1];
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}