#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum[448][100001], isum[448][100001];

void solve() {
	ll n, q; cin >> n >> q;
	ll a[n + 1]; a[0] = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	ll piv = 0;
	while (piv * piv < q) ++piv;
	for (ll i = 1; i < piv; ++i) {
		for (ll j = 0; j <= n; ++j) {
			if (j - i < 0) {
				sum[i][j] = a[j];
				isum[i][j] = a[j];
			} else {
				sum[i][j] = a[j] + sum[i][j - i];
				isum[i][j] = ((j - 1) / i + 1) * a[j] + isum[i][j - i];
			}
		}
	}
	while (q--) {
		ll s, d, k; cin >> s >> d >> k;
		if (d >= piv) {
			ll ans = 0;
			for (ll i = 0; i < k; ++i) {
				ans += (i + 1) * a[s + i * d];
			}
			cout << ans << ' '; continue;
		} else {
			ll ans = isum[d][s + d * (k - 1)];
			if (s - d >= 0) ans -= isum[d][s - d];
			ll m = sum[d][s + d * (k - 1)];
			if (s - d >= 0) m -= sum[d][s - d];
			ans -= m * ((s - 1) / d);
			cout << ans << ' '; continue;
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}