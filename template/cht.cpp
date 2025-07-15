#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// y = ax + b
struct Line {
	mutable ll a, b;
    mutable double p;
	bool operator< (const Line& o) const { return a < o.a; }
	bool operator< (const ll x) const { return p < x; }
};

// maximum
struct LineContainer : multiset<Line, less<>> {
	double div(ll a, ll b) { return (double) a / b; }
	bool bad(iterator x, iterator y) {
		if (y == end()) return x->p = LLONG_MAX, false;
		if (x->a == y->a) x->p = x->b > y->b ? LLONG_MAX : LLONG_MIN;
		else x->p = div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void add(ll a, ll b) {
		auto z = insert({a, b, 0}), y = z++, x = y;
		while (bad(y, z)) z = erase(z);
		if (x != begin() && bad(--x, y)) bad(x, erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) bad(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
};