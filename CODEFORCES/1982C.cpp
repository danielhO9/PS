#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n, l, r; cin >> n >> l >> r;
	ll a[n + 1]; a[0] = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	ll sum[n + 1];
	for (int i = 0; i <= n; ++i) {
		if (i == 0) sum[i] = 0;
		else sum[i] = sum[i - 1] + a[i];
	}
	ll ans[n + 1]; ans[0] = 0;
	for (int i = 1; i <= n; ++i) {
		ans[i] = ans[i - 1];
		ll s = 0, e = i, mid;
		while (s + 1 < e) {
			mid = (s + e) / 2;
			if (sum[mid] <= max(sum[i] - l, 0ll)) s = mid;
			else e = mid;
		}
		if (sum[s] >= sum[i] - r && sum[s] <= sum[i] - l) {
			ans[i] = max(ans[i], ans[s] + 1);
		}
	}
	cout << ans[n] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}