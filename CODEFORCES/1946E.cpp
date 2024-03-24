#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll fac[200001];
ll ifac[200001];
ll n;

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void init() {
	fac[0] = 1ll; ifac[0] = 1ll;
	for (ll i = 1; i <= 2e5; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
		ifac[i] = pow(fac[i], MOD - 2);
	}
}

ll comb(ll a, ll b) {
	ll ans = fac[a];
	ans *= ifac[b]; ans %= MOD;
	ans *= ifac[a - b]; ans %= MOD;
	// cout << a << ' ' << b << ' ' << ans << '\n';
	return ans;
}

ll lquery(ll ind, vector<ll>& p) {
	if (ind == 0) return 1ll;
	ll l = 0, r = p[ind], h = p[ind - 1];
	ll cnt = (r - l);
	ll temp = lquery(ind - 1, p);
	temp *= fac[r - h - 1]; temp %= MOD;
	temp *= comb(cnt - 1, r - h - 1); temp %= MOD;
	return temp;
}

ll rquery(ll ind, vector<ll>& s) {
	if (ind + 1 == s.size()) return 1ll;
	ll l = s[ind], r = n - 1, h = s[ind + 1];
	ll cnt = (r - l);
	ll temp = rquery(ind + 1, s);
	temp *= fac[h - l - 1]; temp %= MOD;
	temp *= comb(cnt - 1, h - l - 1); temp %= MOD;
	return temp;
}

void solve() {
	ll m1, m2; cin >> n >> m1 >> m2;
	vector<ll> p(m1); for (int i = 0; i < m1; ++i) {
		cin >> p[i]; --p[i];
	}
	vector<ll> s(m2); for (int i = 0; i < m2; ++i) {
		cin >> s[i]; --s[i];
	}
	if (p[m1 - 1] != s[0] || p[0] != 0 || s[m2 - 1] != n - 1) { cout << 0 << '\n'; return; }
	ll ans = 1ll, pi = m1 - 1, si = 0;
	ans *= lquery(pi, p); ans %= MOD;
	ans *= rquery(si, s); ans %= MOD;
	ans *= comb(n - 1, n - 1 - s[0]); ans %= MOD;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}