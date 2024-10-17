#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
typedef pair<ll, ll> pll;

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
		if (ret[i + jump] < 0) ret[i + jump] += MOD;
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

ll n;
const ll M = 100005;
pll ran[M];
unordered_map<ll, ll> m;
vector<ll> y;
ll in[2*M], out[2*M];
ll fac[M];
ll inv[M];

ll lpow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = lpow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void init() {
	fac[0] = 1ll;
	for (ll i = 1; i < M; ++i) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= MOD;
	}
	for (int i = 0; i < M; ++i) {
		inv[i] = lpow(fac[i], MOD - 2);
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> ran[i].first >> ran[i].second;
	for (int i = 0; i < n; ++i) ++ran[i].second;
	set<ll> s;
	for (int i = 0; i < n; ++i) {
		s.insert(ran[i].first);
		s.insert(ran[i].second);
	}
	ll idx = 0;
	for (auto i: s) m[i] = idx++;
	for (int i = 0; i < n; ++i) {
		++in[m[ran[i].first]];
		++out[m[ran[i].second]];
	}
	ll cnt = 0;
	for (int i = 0; i < idx; ++i) {
		cnt -= out[i];
		while (in[i]) {
			y.push_back(cnt);
			++cnt; --in[i];
		}
	}
	assert(y.size() == n);
	vector<ll> A(n), B(n);
	for (auto i: y) {
		A[i] += fac[i];
		A[i] %= MOD;
	}
	for (int i = 0; i < n; ++i) {
		B[i] = inv[n - 1 - i];
	}
	auto res = karatsuba_multiply_vec(A, B);
	
	for (int i = n - 1; i < 2 * n - 1; ++i) {
		ll tmp = (res[i] * inv[i - (n - 1)]) % MOD;
		cout << tmp << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}