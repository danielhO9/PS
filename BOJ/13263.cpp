#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll INF = LLONG_MAX;

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
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

void solve() {
	int n; cin >> n;
	vector<ll> a(n), b(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	LineContainer cht;
	// dp(i) = min(dp(j) + b[j] * a[i])
	cht.add(-b[0], 0);
	for (int i = 1; i < n; ++i) {
		if (i == n - 1) {
			cout << -cht.query(a[i]);
			break;
		}
		cht.add(-b[i], cht.query(a[i]));
	}
	if (n == 1) cout << 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}