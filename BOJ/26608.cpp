#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    double slope, y_value;
    mutable double meet;
    ll A, B;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / ((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 300001.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? 300001.0 : 0.0;
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(double slope, double y_value, ll A, ll B) {
        auto ite = insert({slope, y_value, 0, A, B}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

ll gcd(ll A, ll B) {
    if (A < 0) A *= (-1);
    while (A != 0 && B != 0) {
        (A > B ? A : B) = (A > B ? A : B) % (A > B ? B : A);
    }
    return A + B;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll N, M, k; cin >> N >> M >> k;
    LineContainer graph;
    ll A, B;
    for (ll i = 0; i < N; ++i) {
        cin >> A >> B;
        graph.add(k / static_cast<double>(A + B), A / static_cast<double>(A + B), A, B);
    }
    // cout << "\n";
    // for (Line element: graph) {
    //     cout << element.A << " " << element.B << " " << element.meet << endl;
    // }
    ll temp;
    for (ll i = 1; i < M + 1; ++i) {
        auto line = graph.lower_bound(i);
        // line->B - k * i / line->A + k * i
        if (line->B - k * i == 0) cout << "0/0" << "\n";
        else {
            temp = gcd(line->B - k * i, line->A + k * i);
            // cout << line->B - k * i << " " << line->A + k * i << endl;
            // cout << temp << endl;
            cout << (line->B - k * i) / temp << "/" << (line->A + k * i) / temp << "\n";
        }
    }

    return 0;
}