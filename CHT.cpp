#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL INF = LLONG_MAX;

struct Line {
	mutable LL k, m;
    mutable double p;
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (LL x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	double div(LL a, LL b) {
		return (double) a / b;
    }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(LL k, LL m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	LL query(LL x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

struct rLine {
	mutable LL k, m;
    mutable double p;
	bool operator < (const Line& o) const { return k > o.k; }
	bool operator < (LL x) const { return p < x; }
};

struct rLineContainer : multiset<rLine, less<>> {
	double div(LL a, LL b) {
		return (double) a / b;
    }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) x->p = x->m > y->m ? -INF : INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(LL k, LL m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	LL query(LL x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
