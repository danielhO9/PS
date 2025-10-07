/**
 * Description: A `multiset`-based implementation of the Convex Hull Trick.
 *  Supports dynamic insertion of lines and querying for the maximum value at a given point.
 *  Works for lines with non-monotonic slopes. For minimum queries, insert lines with negated coefficients.
 * Time: Both `add` and `query` operations are $O(\log N)$.
 */
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