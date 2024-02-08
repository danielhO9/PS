#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value; mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value > var.y_value;}
		return slope < var.slope;
	}
    bool operator < (double x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 300001.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value >= next(a)->y_value ? 300001.0 : 0.0;
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
    ll N; cin >> N;
    vector<ll> answer(N);
    ll x, y;
    LineContainer graph;
    for (ll i = 0; i < N; ++i) {
        cin >> x >> y;
        if (i == 0) answer[i] = 0;
        else {
            auto line = graph.lower_bound(y / static_cast<double>(x));
            answer[i] = line->slope * y + line->y_value * x;
        }
        graph.add(y, x);

        // cout << "\n" << i << "번째" << "\n";
        // for (Line element: graph) {
        //     cout << element.slope << " " << element.y_value << " " << element.meet << "\n";
        // }
    }
    // for (ll i: answer) {
    //     cout << i << " ";
    // }

    cout << *max_element(answer.begin(), answer.end()) << "\n";
    return 0;
}