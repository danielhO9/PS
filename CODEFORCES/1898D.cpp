#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	LL a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	LL b[n]; for (int i = 0; i < n; ++i) cin >> b[i];
	LL ans = 0;
	LL minn = (LL) 1e9 + 1; LL maxx = 0;
	for (int i = 0; i < n; ++i) {
		minn = min(minn, max(a[i], b[i]));
		maxx = max(maxx, min(a[i], b[i]));
		ans += abs(a[i] - b[i]);
	}
	if (minn < maxx) ans += (maxx - minn) * 2;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}