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
    ios::sync_with_stdio(false); cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> c(n + 1), s(n + 1);
    for (ll i = 0; i < n + 1; ++i) {
        if (i == 0) { c[i] = 0; s[i] = 0; }
        else { cin >> c[i]; s[i] = s[i - 1] + c[i]; }
    }

    vector<ll> answer1(n + 1); answer1[0] = LLONG_MIN;
    vector<Line> graph;
    for (ll i = 1; i < n + 1; ++i) {
        if (i == 1) answer1[i] = LLONG_MIN;
        else {
            int start = 0, end = graph.size() - 1;
            int mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            while (start < end) {
                if (graph[mid].meet < c[i]) end = mid - 1;
                else start = mid;
                mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            }
            answer1[i] = graph[mid].slope * c[i] + graph[mid].y_value - s[i - 1] + i * c[i];
        }
        // {-i, s[i - 1], ?}
        while (!graph.empty() && meetPoint(graph.back(), {-i, s[i - 1], 0}) >= graph.back().meet) graph.pop_back();
        if (graph.empty()) graph.push_back({-i, s[i - 1], 1e9 + 1});
        else graph.push_back({-i, s[i - 1], meetPoint(graph.back(), {-i, s[i - 1], 0})});
    }
    cout << s[n] + *max_element(answer1.begin(), answer1.end()) << "\n";

    vector<ll> answer2(n + 1); answer2[0] = LLONG_MIN;
    graph.clear();
    for (ll i = n; i > 0; --i) {
        if (i == n) answer2[i] = LLONG_MIN;
        else {
            int start = 0, end = graph.size() - 1;
            int mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            while (start < end) {
                if (graph[mid].meet < c[i]) end = mid - 1;
                else start = mid;
                mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
            }
            answer2[i] = graph[mid].slope * c[i] + graph[mid].y_value + s[i] - i * c[i];
        }
        // {i, -s[i], ?}
        while (!graph.empty() && meetPoint(graph.back(), {i, -s[i], 0}) >= graph.back().meet) graph.pop_back();
        if (graph.empty()) graph.push_back({i, -s[i], 1e9 + 1});
        else graph.push_back({i, -s[i], meetPoint(graph.back(), {i, -s[i], 0})});
    }
    cout << s[n] + *max_element(answer2.begin(), answer2.end()) << "\n";
    return 0;
}