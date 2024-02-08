#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Line {
    int slope;
    ll y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return static_cast<double>(((*b).y_value - (*a).y_value) / (static_cast<ll>((*a).slope) - static_cast<ll>((*b).slope)));
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = static_cast<double>(LLONG_MAX); return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? static_cast<double>(LLONG_MAX) : static_cast<double>(-LLONG_MAX);
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(int slope, ll y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }

};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    LineContainer graph;
    // n 입력
    int n; cin >> n;
    // distance 생성
    int distance[100100], p[100100], s[100100];
    for (int i = 0; i < n + 1; i++) {
        if (i > 1) { int temp; cin >> temp;
            distance[i] = distance[i - 1] + temp;
        } else { distance[i] = 0; }
    }
    // p, s 생성
    for (int i = 1; i < n; i++) {
        cin >> p[i] >> s[i];
    }
    // dp 생성
    // dp[i] = min(s[j] * distance[i] + dp[j] + p[j] - distance[j] * s[j]) (1 <= j < i)
    long long dp[100100];

    for (int i = 1; i < n + 1; i++) {
        if (i == 1) {
            dp[i] = 0;
        } else {
            auto line = graph.lower_bound(distance[i]);
            dp[i] = static_cast<ll>(line->slope) * static_cast<ll>(distance[i]) + line->y_value;
        }
        if (i != n) {
            graph.add(s[i], dp[i] + static_cast<ll>(p[i]) - static_cast<ll>(distance[i]) * static_cast<ll>(s[i]));
        }
    }
    cout << dp[n] << endl;
    return 0;
}