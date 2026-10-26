#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 999999893;

LL pow(LL a, LL b) {
	if (b == 0) return 1LL;
	LL half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	return (half * a) % MOD;
}

void solve() {
	LL N; cin >> N;
	if (N % 2 == 1) {
		N /= 2;
		LL ans = pow(2LL, N) - 1;
		LL m = pow(2LL, 2 * N) + pow(2LL, N + 1) - 1;
		if (m < 0) {
			LL temp = abs(m / MOD) + 1;
			m += MOD * temp;
		}
		m %= MOD;
		ans *= pow(m, MOD - 2); ans %= MOD;
		cout << ans << '\n';
	} else {
		N /= 2; --N;
		LL ans = pow(2LL, N + 1) - 1;
		LL m = 1 - pow(2LL, 2 * N + 1) + pow(2LL, N + 2) - 2;
		if (m < 0) {
			LL temp = abs(m / MOD) + 1;
			m += MOD * temp;
		}
		m %= MOD;
		ans *= pow(m, MOD - 2); ans %= MOD;
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}