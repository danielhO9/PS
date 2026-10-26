#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// y = kx + m
struct Line {
	mutable ll k, m;
    mutable double p;
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	double div(ll a, ll b) {
		return (double) a / b;
    }
	bool bad(iterator x, iterator y) {
		if (y == end()) return x->p = LLONG_MAX, 0;
		if (x->k == y->k) x->p = x->m > y->m ? LLONG_MAX : LLONG_MIN;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (bad(y, z)) z = erase(z);
		if (x != begin() && bad(--x, y)) bad(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) bad(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
} cht;

// dp[j] = min(-2hi * hj + dp[i] + hi ^ 2) + C + hj ^ 2
int N;
ll C;
ll h[200000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> C;
	for (int i = 0; i < N; ++i) cin >> h[i];
	ll ans;
	for (int i = 0; i < N; ++i) {
		ll val;
		if (i == 0) val = 0;
		else val = -cht.query(h[i]) + C + h[i] * h[i];
		ans = val;
		cht.add(2ll * h[i], -val - h[i] * h[i]);
	}
	cout << ans;
}