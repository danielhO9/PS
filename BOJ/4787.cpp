#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value < var.y_value;}
		return slope > var.slope;
	}

    bool operator < (int x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) { return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope); }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 1e9 + 1.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value <= next(a)->y_value ? 1e9 + 1.0 : 0.0;
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

ll n, c; ll temp;
vector<ll> lenght(1000001);
vector<ll> dp(1000001);
LineContainer graph;
ll solution(ll n, ll c) {
    graph = {}; for (ll i = 1; i < n + 1; ++i) {dp[i] = 0;}
    for (ll i = 1; i < n + 1; ++i) {
        cin >> lenght[i];
        graph.add(-2 * lenght[i], lenght[i] * lenght[i] + dp[i - 1]);
        auto line = graph.lower_bound(lenght[i]);
        dp[i] = line->slope * lenght[i] + line->y_value + c + lenght[i] * lenght[i];
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    vector<ll> answer;
    while (true) {
        cin >> n >> c;
        if (n == 0) break;
        answer.push_back(solution(n, c));
    }
    for (ll element: answer) cout << element << "\n";

    return 0;
}