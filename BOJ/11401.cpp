#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 1000000007;

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void solve() {
	ll N, K; cin >> N >> K;
	ll m = 1, c = 1;
	for (ll i = 1; i <= K; ++i) {
		c *= (N - i + 1); c %= MOD;
		m *= i; m %= MOD;
	}
	m = pow(m, MOD - 2);
	ll ret = m * c; ret %= MOD;
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}