#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value;
    double meet;
};

double meetPoint(Line& line1, const Line& line2) {
    return (line2.y_value - line1.y_value) / static_cast<double>(line1.slope - line2.slope);
}

int main() {
    ll N; cin >> N;
    vector<ll> s(N + 1), ss(N + 1);
    ll temp;
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) { s[i] = 0; ss[i] = 0; }
        else {
            cin >> temp;
            s[i] = s[i - 1] + temp;
            ss[i] = ss[i - 1] + i * temp;
        }
    }

    vector<ll> dp(N + 1); vector<Line> graph;
    vector<ll> answer;
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) dp[i] = 0;
        else {
            int start = 0, end = graph.size() - 1;
            int mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            while (start < end) {
                if (graph[mid].meet < s[i - 1]) end = mid - 1;
                else start = mid;
                mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            }
            dp[i] = graph[mid].slope * s[i - 1] + graph[mid].y_value + ss[i - 1];
        }
        answer.push_back(dp[i] + ss[N] - ss[i] - i * (s[N] - s[i]));

        // {-i, -ss[i] + i * s[i] + dp[i], ?}
        while (!graph.empty() && meetPoint(graph.back(), {-i, -ss[i] + i * s[i] + dp[i], 0}) >= graph.back().meet) graph.pop_back();
        if (graph.empty()) graph.push_back({-i, -ss[i] + i * s[i] + dp[i], 1e12 + 1});
        else graph.push_back({-i, -ss[i] + i * s[i] + dp[i], meetPoint(graph.back(), {-i, -ss[i] + i * s[i] + dp[i], 0})});
        // cout << i << "번째" << endl;
        // for (Line element: graph) {
        //     cout << element.slope << " " << element.y_value << " " << element.meet << endl;
        // }
    }
    // for (ll element: answer) {
    //     cout << element << " ";
    // }

    cout << *max_element(answer.begin(), answer.end()) << "\n";
    return 0;
}