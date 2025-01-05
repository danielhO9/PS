#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll fac[2000001];
ll ifac[2000001];

ll lpow (ll a, ll b) {
	if (b == 0) return 1;
	ll half = lpow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

void init() {
	ll num = 1;
	fac[0] = 1; ifac[0] = 1;
	for (ll i = 1; i <= 2e6; ++i) {
		num *= i; num %= MOD;
		fac[i] = num;
		ifac[i] = lpow(num, MOD - 2);
	}
}

ll comb(ll a, ll b) {
	assert(a >= b);
	ll ret = fac[a];
	ret *= ifac[b]; ret %= MOD;
	ret *= ifac[a - b]; ret %= MOD;
	return ret;
}

ll A, B, N;

void solve() {
	cin >> A >> B >> N;
	int T; cin >> T;
	init();
	while (T--) {
		ll ans = 0;
		ll n, r; cin >> n >> r;
		--r; n = N - n;
		// cout << n << ' ' << r << ' ';
		ll add = A + B * N;
		add %= MOD;
		add *= comb(n, r);
		add %= MOD;
		ans += add;

		ll sub = comb(n + 1, r + 1);
		if (r > 0) sub += comb(n, n - r + 1); sub %= MOD;
		sub *= B; sub %= MOD;
		ans -= sub;
		ans += MOD;
		ans %= MOD;
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
1 2 4
1
3 2

1 2 4
10
1 1
1 2
1 3
1 4
2 1
2 2
2 3
3 1
3 2
4 1
*/