#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll N;
ll fac[20000001];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

ll comb(ll n, ll r) {
	ll ret = fac[n];
	ret *= pow(fac[n - r], MOD - 2);
	ret %= MOD;
	ret *= pow(fac[r], MOD - 2);
	ret %= MOD;
	return ret;
}

void solve() {
	cin >> N;
	fac[0] = 1ll;
	for (ll i = 1; i < 20000001; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
	}
	if (N % 2) {
		ll ret = comb(2 * N, N);
		// cout << ret << ' ';
		ret *= pow(2ll, MOD - 2); ret %= MOD;
		cout << ret;
	} else {
		ll ret = comb(2 * N, N) - comb(N, N / 2);
		if (ret < 0) ret += MOD; ret %= MOD;
		ret *= pow(2ll, MOD - 2); ret %= MOD;
		cout << ret;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}