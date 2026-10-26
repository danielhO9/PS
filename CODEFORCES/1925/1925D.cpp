#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 1e9 + 7;

LL pow(LL a, LL b) {
	a %= MOD;
	if (b == 0) return 1;
	if (b == 1) return a;
	LL half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void solve() {
	LL n, m, k; cin >> n >> m >> k;
	LL times = n * (n - 1) / 2; times %= MOD;
	LL sum = m, psum = 0;
	for (int i = 0; i < m; ++i) {
		LL a, b, f; cin >> a >> b >> f;
		psum += f;
	}
	LL ans = 0; psum %= MOD;
	for (LL i = 0; i < k; ++i) {
		// cout << sum << ' ' << psum << '\n';
		LL temp = psum;
		temp *= pow(pow(times, i + 1), MOD - 2); temp %= MOD;
		ans += temp; ans %= MOD;
		LL a = sum, b = psum;
		sum = a * times; sum %= MOD;
		psum = b * times + a; psum %= MOD;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}