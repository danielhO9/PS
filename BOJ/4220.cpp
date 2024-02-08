#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value > var.y_value;}
		return slope < var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = static_cast<double>(1e9 + 2); return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value < next(a)->y_value ? 0.0 : static_cast<double>(1e9 + 2);
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

struct Machine {
    ll d, p, r, g;

    bool operator < (const Machine& var) const {
		return d < var.d;
	}
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    LineContainer graph;
    multiset<Machine, less<>> Machines;

    ll N, C, D;
    ll d, p, r, g;
    ll case_count = 0;
    while (true) {
        ++case_count;
        cin >> N >> C >> D;
        if (N == 0 && C == 0 && D == 0) break;

        for (ll i = 0; i < N + 1; ++i) {
            if (i == 0) Machines.insert({0, 0, 0, 0});
            else {
                cin >> d >> p >> r >> g;
                Machines.insert({d, p, r, g});
            }
        }

        ll value;
        for (Machine element: Machines) {
            if (graph.empty()) value = C;
            else {
                auto line = graph.lower_bound(element.d);
                value = line->slope * element.d + line->y_value;               
            }
            if (value >= element.p) graph.add(element.g, value + element.r - element.p - element.d * element.g - element.g);
            // for (Line line: graph) {
            //     cout << line.slope << " " << line.y_value << endl;
            // }
            // cout << "\n";
        }
        auto line = graph.lower_bound(D + 1);
        cout << "Case " << case_count << ": " << line->slope * (D + 1) + line->y_value << "\n";
        graph.clear(); Machines.clear();
    }

    return 0;
}