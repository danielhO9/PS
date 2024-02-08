#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line1 {
    ll slope, y_value; mutable double meet;

    bool operator < (const Line1& var) const {
        if (slope == var.slope) {return y_value > var.y_value;}
		return slope < var.slope;
	}
    bool operator < (double x) const {return meet < x;}
};

struct LineContainer1: set<Line1, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 1e6 + 1; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value >= next(a)->y_value ? 1e6 + 1 : -(1e6 + 1);
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
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? 1e6 + 1 : -(1e6 + 1);
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
    ll N, Q; cin >> N >> Q;
    ll a, b; LineContainer1 graph1; LineContainer2 graph2;
    for (ll i = 0; i < N; ++i) {
        cin >> a >> b;
        graph1.add(a, b); graph2.add(a, b);
    }
    double x; ll x_temp; ll answer; ll temp;
    for (ll i = 0; i < Q; ++i) {
        cin >> x >> a;
        x_temp = x * 10.0;
        if (a == 1) {
            auto line = graph1.lower_bound(x);
            answer = line->slope * x_temp + line->y_value * 10;
        } else {
            auto line = graph2.lower_bound(x);
            answer = line->slope * x_temp + line->y_value * 10;
        }
        if (answer % 10 == 0) cout << answer / 10 << ".0000" << "\n";
        else {
            temp = abs(answer) % 10;
            cout << answer/10 << "." << temp << "000" << "\n";
        }
    }


    return 0;
}