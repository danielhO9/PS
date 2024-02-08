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
        if (next(a) == end()) { a->meet = 200001.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value < next(a)->y_value ? 0 : 200001.0;
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
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll N; cin >> N;
    vector<ll> A(N + 1), S(N + 1);
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) {
            A[i] = 0; S[i] = 0;
        }
        else {
            cin >> A[i];
            S[i] = S[i - 1] + A[i];
        }
    }

    vector<ll> answer1(N + 1), answer2(N + 1);
    answer1[0] = 0; answer2[0] = 0;
    LineContainer graph;
    for (ll i = 1; i < N + 1; ++i) {
        if (i == 1) answer1[i] = 0;
        else {
            auto line = graph.lower_bound(i);
            answer1[i] = line->slope * i + line->y_value - S[i];
        }
        graph.add(A[i], S[i] - A[i] * i);
    }

    graph.clear();
    for (ll i = N; i > 0; --i) {
        if (i == N) answer2[i] = 0;
        else {
            auto line = graph.lower_bound(i);
            answer2[i] = line->slope * i + line->y_value - S[i - 1];
        }
        graph.add(A[i], S[i - 1] - A[i] * i);
    }
    
    ll answer = max(*max_element(answer1.begin(), answer1.end()), *max_element(answer2.begin(), answer2.end()));

    for (ll i = 1; i < N + 1; ++i) answer += i * A[i];
    
    cout << answer << "\n";
    return 0;
}