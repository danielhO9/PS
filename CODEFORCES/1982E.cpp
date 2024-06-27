#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
vector<ll> cache[61][61];

ll calc(ll x) {
	x %= MOD;
	return ((x * (x + 1)) / 2) % MOD;
}

// 0 ~ n - 1, 0 ~ k
void init() {
	for (ll i = 0; i <= 60; ++i) cache[0][i] = {1, 1, calc(1)};
	for (ll i = 1; i <= 60; ++i) {
		for (ll j = 0; j <= 60; ++j) {
			auto left = cache[i - 1][j];
			vector<ll> right;
			if (j == 0) right = {0, 0, 0};
			else right = cache[i - 1][j - 1];
			ll val = left[2] + right[2]; val %= MOD;
			val -= calc(left[1]);
			val -= calc(right[0]);
			while (val < 0) val += MOD;
			val %= MOD;
			val += calc(left[1] + right[0]);
			val %= MOD;
			ll l = left[0];
			if (left[0] == (1ll << (i - 1))) l += right[0];
			ll r = right[1];
			if (right[1] == (1ll << (i - 1))) r += left[1];
			cache[i][j] = {l, r, val};
		}
	}
}

vector<ll> func(ll n, ll k) {
	// cout << n << ' ' << k << '\n';
	if (k == -1) return {0, 0, 0};
	ll m = 1ll, cnt = 0;
	while (m * 2 <= n) {
		m *= 2; ++cnt;
	}
	if (__builtin_popcount(n) == 1) return cache[cnt][k];
	auto left = cache[cnt][k];
	auto right = func(n - m, k - 1);
	ll val = left[2] + right[2]; val %= MOD;
	val -= calc(left[1]);
	val -= calc(right[0]);
	while (val < 0) val += MOD;
	val %= MOD;
	val += calc(left[1] + right[0]);
	val %= MOD;
	ll l = left[0];
	if (left[0] == (1ll << cnt)) l += right[0];
	ll r = right[1];
	if (right[1] == n - m) r += left[1];
	return {l, r, val};
}

void solve() {
	ll n, k; cin >> n >> k;
	cout << func(n, k)[2] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}