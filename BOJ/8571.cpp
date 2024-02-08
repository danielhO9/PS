#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line2 {
    ll slope, y_value; mutable double meet;

    bool operator < (const Line2& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}
    bool operator < (double x) const {return meet < x;}
};

struct LineContainer2: set<Line2, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 1e6 + 1; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? 1e6 + 1 : 0;
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(ll slope, ll y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    vector<ll> c(n + 1); LineContainer2 graph;
    vector<ll> dp(n + 1);
    for (ll i = 0; i < n; ++i) cin >> c[i + 1];
    for (ll i = n; i >= 0; --i) {
        if (i != n) {
            auto line = graph.lower_bound(i);
            dp[i] = line->slope * i + line->y_value;
        }
        graph.add(-c[i], c[i] * i + dp[i]);
    }
    cout << dp[0];
    return 0;
}