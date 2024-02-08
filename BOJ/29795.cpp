#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, Q;
double MAX_X = 1e18;

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
    double meetPoint(iterator a, iterator b) { return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope); }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = MAX_X; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value >= next(a)->y_value ? MAX_X : 0.0;
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

LineContainer graph; ll answer, goal, temp;
LineContainer::iterator line; ll multianswer;

ll multitime(ll x, ll y) {
    if (y == 0) return 1;
    ll tmp = multitime(x, y / 2);
    if (y % 2 == 0) return tmp * tmp;
    else return tmp * tmp * x;
}
pair<ll, ll> cal1(ll x, ll y, ll value) {
    x += line->y_value * value;
    while (x < y) {
        if (x > line->meet) break;
        ++value; x += line->y_value;
    }
    return {value, x};
}
ll multi_temp;

pair<ll, ll> cal2(ll x, ll y, ll value) {
    multi_temp = multitime(line->slope, value);
    x = multi_temp * x + line->y_value * ((multi_temp - 1) / (line->slope - 1));
    while (x < y) {
        if (x > line->meet) break;
        ++value; x = line->slope * x + line->y_value;
    }
    return {value, x};
}
pair<ll, ll> pa_temp;

ll solution(ll x, ll y) {
    answer = 0;
    line = graph.lower_bound(x);
    if (x >= y) return 0;
    if (line->slope * x + line->y_value <= x) return -1;
    while (true) {
        if (line->meet < x) {
            line = graph.lower_bound(x);
        }
        goal = line->meet;
        if (goal > y) goal = y;
        if (line->slope == 1) {
            temp = (goal - x) / static_cast<double>(line->y_value);
            pa_temp = cal1(x, y, temp); answer += pa_temp.first; x = pa_temp.second;
        } else {
            temp = log((goal * (line->slope - 1) + line->y_value) / (line->slope * x + line->y_value - x)) / log(line->slope);
            pa_temp = cal2(x, y, temp); answer += pa_temp.first; x = pa_temp.second;
        }
        if (x >= y) return answer;
        ++line;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    ll a, b;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        graph.add(a, b);
    }
    ll x, y;
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        cout << solution(x, y) << "\n";
    }
    return 0;
}
