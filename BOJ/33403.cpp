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

// maximum
template<class T>
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
	T query(T x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

ll k, n;
ll I[100001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i <= n; ++i) cin >> I[i];
    double ans = 0.0;
    LineContainer<ll> cht;
    for (int i = 0; i < k; ++i) {
        cht.clear();
        for (int j = i; j < n; j += k) cht.add(I[j + 1] - I[j], I[j]);
        double tans = 0.0;
        double cur = 0.0;
        for (auto j: cht) {
            if (j.p < 0.0) continue;
            tans += (j.k * (min(j.p, 1.0) + cur) + j.m * 2.0) * (min(j.p, 1.0) - cur) / 2.0;
            if (j.p > 1.0) break;
            cur = j.p;
        }
        ans += tans * (n / k);
        if (i < n % k) ans += tans;
    }
    cout << fixed;
    cout.precision(7);
    cout << ans;
}