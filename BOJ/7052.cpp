#include <bits/stdc++.h>
using namespace std;

struct Line {
    int slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value > var.y_value;}
		return slope < var.slope;
	}

    bool operator < (int x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) { return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope); }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 2e8 + 1.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value >= next(a)->y_value ? 2e8 + 1.0 : 0.0;
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(int slope, int y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }

};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n; vector<int> s(n), d(n);
    vector<int> W = {0}, S = {0};
    int value = 0;
    LineContainer graph;
    for (int i = 0; i < n; ++i) cin >> s[i] >> d[i];
    reverse(s.begin(), s.end()); reverse(d.begin(), d.end());
    for (int i = 1; i <= n; ++i) {
        W.push_back(W.back() + s[i - 1]);
        S.push_back(S.back() + d[i - 1]);
        value += s[i - 1] * S[i];
    }
    vector<int> dp(n + 1, value);
    for (int i = 1; i <= n; ++i) {
        graph.add(S[i], -S[i] * W[i - 1]);
        if (i != 1) {
            auto line = graph.lower_bound(W[i - 1]);
            dp[i] -= line->slope * W[i - 1] + line->y_value + (W[n] - W[i - 1]) * S[i];
        }
    }
    cout << *min_element(dp.begin(), dp.end());

    return 0;
}