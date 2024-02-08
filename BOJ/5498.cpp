#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value; double meet;
};

double meetPoint(Line& line1, const Line& line2) {
    return (line2.y_value - line1.y_value) / static_cast<double>(line1.slope - line2.slope);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll N, S; cin >> N;cin >> S;
    vector<ll> T(N + 1), F(N + 1), answer(N + 1);
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) {
            T[i] = 0; F[i] = 0;
        } else {
            ll t, f; cin >> t >> f;
            T[i] = T[i - 1] + t; F[i] = F[i - 1] + f;
        }
    }
    deque<Line> graph;
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) answer[i] = 0;
        else {
            while (graph.size() > 1 && graph[1].meet <= T[i]) graph.pop_front();
            answer[i] = graph.front().slope * T[i] + graph.front().y_value + S * F[N] + T[i] * F[i];
        }
        // {-F[i], answer[i] - S * F[i], ?}
        while (!graph.empty() && graph.back().meet >= meetPoint(graph.back(), {-F[i], answer[i] - S * F[i], 0})) graph.pop_back();
        if (graph.empty()) graph.push_back({-F[i], answer[i] - S * F[i], 0});
        else graph.push_back({-F[i], answer[i] - S * F[i], meetPoint(graph.back(), {-F[i], answer[i] - S * F[i], 0})});
    }
    // for (ll i = 0; i < N + 1; ++i) {
    //     cout << answer[i] << " ";
    // }
    cout << answer[N] << "\n";

    return 0;
}
