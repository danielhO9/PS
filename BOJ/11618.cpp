#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e6 + 3;

vector<ll> basic_multiply_vec(const vector<ll> &x, const vector<ll> &y) {
	vector<ll> ret(x.size() + y.size() + 1, 0);
	for (ll i = 0; i < x.size(); ++i) {
		for (ll j = 0; j < y.size(); ++j) {
			ret[i + j] += (x[i] * y[j]) % MOD;
			ret[i + j] %= MOD;
		}
	}
	return ret;
}

vector<ll> add(const vector<ll> &x, const vector<ll> &y, ll jump, ll times) {
	ll sz = max((ll)x.size(), (ll)y.size() + jump) + 2;
	vector<ll> ret = vector<ll>(x.begin(), x.end());
	while (ret.size() < sz)
		ret.push_back(0);

	for (ll i = 0; i < y.size(); ++i) {
		ret[i + jump] += (y[i] * times) % MOD;
		ret[i + jump] %= MOD;
	}
	return ret;
}

vector<ll> karatsuba_multiply_vec(const vector<ll> &x, const vector<ll> &y) {
	ll sz = max(x.size(), y.size());
	if (sz <= 100)
		return basic_multiply_vec(x, y);
	ll m = sz / 2;

	// x = x0 + x1 * (10 ** m)
	vector<ll> x0 = vector<ll>(x.begin(), x.begin() + min((ll)x.size(), m));
	vector<ll> x1 = vector<ll>(x.begin() + min((ll)x.size(), m), x.end());

	// y = y0 + y1 * (10 ** m)
	vector<ll> y0 = vector<ll>(y.begin(), y.begin() + min((ll)y.size(), m));
	vector<ll> y1 = vector<ll>(y.begin() + min((ll)y.size(), m), y.end());

	// z2 = x1 * y1
	vector<ll> z2 = karatsuba_multiply_vec(x1, y1);

	// z0 = x0 * y0
	vector<ll> z0 = karatsuba_multiply_vec(x0, y0);

	// z1 = (x0 + x1) * (y0 + y1)
	x0 = add(x0, x1, 0, 1);
	y0 = add(y0, y1, 0, 1);
	vector<ll> z1 = karatsuba_multiply_vec(x0, y0);

	// z1 -= (z2 + z0) = x1 * y0 + y1 * x0
	z1 = add(z1, z2, 0, -1);
	z1 = add(z1, z0, 0, -1);

	// z2 * (10 ** 2m) + z1 * (10 ** m) + z0
	z0 = add(z0, z2, 2 * m, 1);
	z0 = add(z0, z1, m, 1);
	return z0;
}


ll fac[400001];
ll apow[400001], bpow[400001];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

ll comb(ll n, ll r) {
	ll ret = fac[n];
	ret *= pow(fac[r], MOD - 2); ret %= MOD;
	ret *= pow(fac[n - r], MOD - 2); ret %= MOD;
	return ret;
}

ll n, a, b, c;
ll ans = 0ll;

void solve() {
	cin >> n >> a >> b >> c;
	fac[0] = 1ll, fac[1] = 1ll;
	apow[0] = 1ll, apow[1] = a;
	bpow[0] = 1ll, bpow[1] = b; 
	for (ll i = 2; i <= 2 * n; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
		apow[i] = apow[i - 1] * a;
		apow[i] %= MOD;
		bpow[i] = bpow[i - 1] * b;
		bpow[i] %= MOD;
	}
	for (ll i = 0; i < n; ++i) {
		ll tmp; cin >> tmp;
		if (i == 0) continue;
		tmp *= comb(n - 1 + n - 2 - i, n - 2); tmp %= MOD;
		tmp *= apow[n - 1]; tmp %= MOD;
		tmp *= bpow[n - 1 - i]; tmp %= MOD;
		ans += tmp; ans %= MOD;
	}
	for (ll i = 0; i < n; ++i) {
		ll tmp; cin >> tmp;
		if (i == 0) continue;
		tmp *= comb(n - 1 + n - 2 - i, n - 2); tmp %= MOD;
		tmp *= bpow[n - 1]; tmp %= MOD;
		tmp *= apow[n - 1 - i]; tmp %= MOD;
		ans += tmp; ans %= MOD;
	}
	vector<ll> A, B;
	for (ll i = 0; i < n - 1; ++i) {
		ll tmp = apow[i];
		tmp *= pow(fac[i], MOD - 2);
		tmp %= MOD;
		A.push_back(tmp);
	}
	for (ll i = 0; i < n - 1; ++i) {
		ll tmp = bpow[i];
		tmp *= pow(fac[i], MOD - 2);
		tmp %= MOD;
		B.push_back(tmp);
	}
	// cout << A.size() << '\n';
	// cout << B.size() << '\n';
	vector<ll> mul = karatsuba_multiply_vec(A, B);
	while (mul.back() == 0) mul.pop_back();
	// cout << mul.size() << '\n';
	for (auto& i: mul) i %= MOD;
	for (ll i = 0; i < mul.size(); ++i) {
		ll tmp = 1ll;
		tmp *= fac[i]; tmp %= MOD;
		tmp *= mul[i]; tmp %= MOD;
		tmp *= c; tmp %= MOD;
		ans += tmp; ans %= MOD;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}