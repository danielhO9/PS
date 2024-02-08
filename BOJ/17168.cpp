#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct box {
    ll h, w;

    bool operator < (const box& var) const {
        if (h == var.h) {return w <= var.w;}
		return h < var.h;
	}
};

struct Line {
    ll slope, y_value;
    double meet;
};

double meetPoint(Line& line1, const Line& line2) {
    return (line2.y_value - line1.y_value) / static_cast<double>(line1.slope - line2.slope);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    multiset<box, less<>> plane;
    ll N, a, b; cin >> N;
    vector<ll> h(N + 1), w(N + 1); h[0] = 0; w[0] = 0;
    ll H = 0, S = 0;
    for (ll i = 0; i < N; ++i) {
        cin >> a >> b;
        h[i + 1] = (a > b ? a : b); w[i + 1] = (a > b ? b : a);
        H += h[i + 1];
        S += w[i + 1] * h[i + 1];
        plane.insert({h[i + 1], w[i + 1]});
    }
    vector<Line> graph; vector<ll> answer;
    for (box box: plane) {

        while (!graph.empty() && graph.back().meet <= box.h) graph.pop_back();
        if (!graph.empty()) answer.push_back(graph.back().slope * box.h + graph.back().y_value + box.w * box.h - S);

        // {-h[i], h[i] * (w[i] + H - h[i]), ?}
        if (!graph.empty() && graph.back().slope == -box.h) {
            if (graph.back().y_value >= box.h * (box.w + H - box.h)) continue;
            else graph.pop_back();
        }
        while (!graph.empty() && meetPoint(graph.back(), {-box.h, box.h * (box.w + H - box.h), 0}) >= graph.back().meet) graph.pop_back();
        if (graph.empty()) graph.push_back({-box.h, box.h * (box.w + H - box.h), 1e6 + 1});
        else graph.push_back({-box.h, box.h * (box.w + H - box.h), meetPoint(graph.back(), {-box.h, box.h * (box.w + H - box.h), 0})});
    }
    cout << *max_element(answer.begin(), answer.end()) << "\n";
    return 0;
}