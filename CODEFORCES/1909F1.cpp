#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

void solve() {
	LL n; cin >> n;
	vector<LL> a(n); for (LL i = 0; i < n; ++i) cin >> a[i];
	LL p = 0LL, ans = 1LL;
	for (LL i = 0; i < n; ++i) {
		if (a[i] > i + 1) ans = 0LL;
		if (p == a[i]) ans = ans;
		else if (p + 1 == a[i]) {
			ans *= (i + 1 - p) + (i - p);
			ans %= MOD;
		} else if (p + 2 == a[i]) {
			ans *= (i - p);
			ans %= MOD;
			ans *= (i - p);
			ans %= MOD;
		} else {
			ans = 0LL;
		}
		p = a[i];
	}
	if (p != n) ans = 0LL;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}