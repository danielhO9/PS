#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value; mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 1e6 + 1; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? 1e6 + 1 : -1.0;
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
    vector<ll> h(n + 1), w(n + 1), s(n + 1);
    for (ll i = 0; i < n + 1; ++i) {
        if (i == 0) h[i] = 0;
        else cin >> h[i];
    }
    for (ll i = 0; i < n + 1; ++i) {
        if (i == 0) { w[i] = 0; s[i] = 0; }
        else { cin >> w[i]; s[i] = s[i - 1] + w[i];}
    }

    LineContainer graph;
    vector<ll> answer(n + 1); answer[0] = 0;
    for (ll i = 1; i < n + 1; ++i) {
        if (i == 1) answer[i] = 0;
        else {
            Line line = *graph.lower_bound(h[i]);
            answer[i] = line.slope * h[i] + line.y_value + h[i] * h[i] + s[i - 1];
        }
        graph.add(h[i] * (-2), answer[i] + h[i] * h[i] - s[i]);
        // for (Line element: graph) cout << i << "번째 " << element.slope << " " << element.y_value << " " << element.meet << "\n";
        // cout << "\n";
    }
    // for (ll i = 0; i < n + 1; ++i) cout << answer[i] << " ";
    cout << answer[n] << "\n";
    return 0;
}