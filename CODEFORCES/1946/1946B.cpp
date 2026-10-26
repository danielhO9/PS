#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll twoPow(ll k) {
	if (k == 0) return 1ll;
	ll half = twoPow(k / 2);
	half = half * half; half %= MOD;
	if (k % 2 == 0) return half;
	return (half * 2ll) % MOD;
}

void solve() {
	ll n, k; cin >> n >> k;
	vector<ll> a(n + 1); for (int i = 1; i <= n; ++i) cin >> a[i]; a[0] = 0;
	vector<ll> sum(n + 1); sum[0] = 0;
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
	ll mins = 0, maxs = 0;
	for (int i = 1; i <= n; ++i) {
		maxs = max(maxs, sum[i] - mins);
		mins = min(mins, sum[i]);
	}
	ll ans = sum[n]; maxs %= MOD;
	while (ans < 0) ans += MOD;
	ans %= MOD;
	ll temp = maxs * (twoPow(k) + MOD - 1);
	ans += temp;
	ans %= MOD;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}