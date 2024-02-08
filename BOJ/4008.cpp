#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL INF = LLONG_MAX;

int n;
LL a, b, c, x[1000001];

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
		while (begin()->p < x) erase(begin());
        return begin()->k * x + begin()->m;
	}
};

// dp[i] = max(-2aXj * Xi + (aXj^2 - bXj + dp[j])) + (aXi^2 + bXi + c)
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    cin >> a >> b >> c;
    LL temp, dp;
    LineContainer graph;
    graph.add(0, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> temp;
        x[i] = x[i - 1] + temp;
        dp = graph.query(x[i]) + a * x[i] * x[i] + b * x[i] + c;
        graph.add((-2) * a * x[i], a * x[i] * x[i] - b * x[i] + dp);
    }
    cout << dp;
}