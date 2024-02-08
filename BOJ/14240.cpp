#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Line {
    int slope;
    ll y_value;
    double meet;
};

double meetPoint(Line& line1, Line& line2) {return static_cast<double>((line2.y_value - line1.y_value) / (static_cast<double>(line1.slope) - static_cast<double>(line2.slope)));}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n; cin >> n;
    vector<ll> s, ss;
    for (int i = 0; i < n + 1; i++) {
        int temp;
        if (i == 0) { s.push_back(0); ss.push_back(0); }
        else {
            cin >> temp;
            s.push_back(s.back() + static_cast<ll>(temp));
            ss.push_back(ss.back() + s.back());
        }
    }

    vector<Line> graph;
    vector<ll> answer;

    for (int i = 1; i < n + 1; i++) {
        if (graph.size() == 0) graph.push_back({-i, 0, numeric_limits<double>::max()});
        else {
            Line temp = {-i, ss[i - 2], 0};
            while (graph.size() > 0 && graph.back().meet <= meetPoint(graph.back(), temp)) {
                graph.pop_back();
            }
            temp.meet = meetPoint(graph.back(), temp);
            graph.push_back(temp);
        }

        int start = 0, end = graph.size() - 1;
        int mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
        while (start < end) {
            if (graph[mid].meet < s[i]) end = mid - 1;
            else start = mid;
            mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
        }
        answer.push_back(static_cast<ll>(graph[mid].slope) * s[i] + graph[mid].y_value + s[i] * static_cast<ll>(i + 1) - ss[i - 1]);

    }

    // for (int i = 0; i < n + 1; i++) {
    //     cout << s[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < n + 1; i++) {
    //     cout << ss[i] << " ";
    // }
    // cout << endl;
    // for (Line element: graph) {
    //     cout << element.slope << " " << element.y_value << " " << element.meet << endl;
    // }
    // cout << endl;
    ll max_value = *max_element(answer.begin(), answer.end());
    cout << max(max_value, 0LL) << endl;

    return 0;
}