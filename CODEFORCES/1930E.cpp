#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll fact[1000001];
ll inv_fact[1000001];

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void init() {
	fact[0] = 1;
	for (ll i = 1; i <= 1e6; ++i) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= MOD;
	}
	for (ll i = 0; i <= 1e6; ++i) {
		inv_fact[i] = pow(fact[i], MOD - 2);
	}
}

ll comb(ll a, ll b) {
	if (a < b) return 0;
	ll amb = inv_fact[a - b];
	a = fact[a]; b = inv_fact[b];
	ll ret = a;
	ret *= amb; ret %= MOD;
	ret *= b; ret %= MOD;
	return ret;
}

void solve() {
	ll n; cin >> n;
	for (ll k = 1; k <= (n - 1) / 2; ++k) {
		ll ans = 1;
		for (ll x = n - 2 * k; x > 0; x -= 2 * k) {
			ans += comb(n, x) - comb(x + 2 * k - 1, 2 * k - 1);
			ans += MOD;
			ans %= MOD;
		}
		cout << ans << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}