#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Line {
    ld slope, y_value; mutable ld meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}
    bool operator < (ld x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    ld meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<ld>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = static_cast<ld>(LLONG_MAX); return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? static_cast<ld>(LLONG_MAX) : 0;
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(ld slope, ld y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

int main() {
    ll n, p, c; cin >> n >> p >> c;
    ll t, x, y;
    LineContainer graph; ld temp_y;
    graph.add(1.0, 0.0);
    for (ll i = 0; i < p; ++i) {
        cin >> t >> x >> y;
        auto line = graph.lower_bound(t);
        temp_y = static_cast<ld>(c) + line->slope * t + line->y_value - (y * t) / static_cast<ld>(x);
        graph.add(y / static_cast<ld>(x), temp_y);
    }
    ld answer = 0.0;
    for (Line line: graph) {
        answer = max(answer, (n - line.y_value) / line.slope);
    }
    cout << fixed;
    cout.precision(7);
    cout << answer;
    return 0;
}