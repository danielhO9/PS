#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n, k, d; cin >> n >> k >> d;
	vector<LL> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<LL> v(k + 1); for (int i = 1; i <= k; ++i) cin >> v[i];
	LL ans = 0, th = 1, now = 1;
	while (true) {
		if (th > d) break;
		LL same = 0, avail = 0;
		for (LL i = 0; i < n; ++i) {
			if (a[i] == i + 1) ++same;
			if (a[i] <= i + 1) ++avail;
		}
		if (ans > avail + (d - th) / 2) break;
		ans = max(ans, same + (d - th) / 2);
		// cout << same << ' ' << (d - th) / 2 << ' ' << ans << '\n';
		for (int i = 0; i < v[now]; ++i) ++a[i];
		++now; ++th;
		if (now > k) now = 1;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}