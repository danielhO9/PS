#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll MOD = 998244353;

ll fac[1000001], ifac[1000001];
ll a[1000001], b[1000001];
ll asum[1000001], bsum[1000001];
ll cache[1000001];
ll n, q;

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	return (half * a) % MOD;
}

ll comb(ll n, ll r) { return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD; }

void init() {
	fac[0] = 1;
	for (ll i = 1; i <= bsum[n]; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
	}
	for (ll i = 0; i <= bsum[n]; ++i) {
		ifac[i] = pow(fac[i], MOD - 2);
	}
	cache[0] = 1;
	for (ll i = 1; i <= bsum[n]; ++i) {
		cache[i] = cache[i - 1] + comb(bsum[n], i);
		cache[i] %= MOD;
	}
}

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	asum[0] = 0, bsum[0] = 0;
	for (int i = 1; i <= n; ++i) {
		asum[i] = asum[i - 1] + a[i];
		bsum[i] = bsum[i - 1] + b[i];
	}
	init();
	while (q--) {
		ll l, r; cin >> l >> r;
		ll ta = asum[r] - asum[l - 1];
		ll tb = bsum[r] - bsum[l - 1];
		ll temp = (bsum[n] - tb + (asum[n] - ta) - ta);
		// cout << temp << ' ';
		cout << (cache[bsum[n]] - (temp < 0 ? 0 : cache[min(bsum[n], temp)]) + MOD) % MOD * pow(cache[bsum[n]], MOD - 2) % MOD << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}