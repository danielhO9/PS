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
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll N; cin >> N;
    vector<ll> s(N + 1);
    for (ll i = 0; i < N + 1; ++i) {
        if (i == 0) s[i] = 0;
        else {
            ll temp; cin >> temp;
            s[i] = s[i - 1] + temp;
        }
    }

    vector<ll> A(N + 1);
    deque<Line> graph;
    // A 입력 -> graph 추가
    for (ll i = 0; i < N + 1; ++i) {
        while (graph.size() > 1 && graph[1].meet <= i) graph.pop_front();
        if (i == 0) A[i] = 0;
        else if (s[i - 1] != s[i]) A[i] = graph.front().slope * i + graph.front().y_value + i * (s[i] + 1);
        else A[i] = A[i - 1];
        if (i != N && (i == 0 || s[i - 1] != s[i])) {
            Line line = {-s[i], A[i], 0};
            while (!graph.empty() && graph.back().meet >= meetPoint(graph.back(), line)) graph.pop_back();
            if (graph.empty()) graph.push_back(line);
            else {
                line.meet = meetPoint(graph.back(), line);
                graph.push_back(line);
            }
        }
        // cout << i << "번째" << endl;
        // for (Line element: graph) {
        //     cout << element.slope << " " << element.y_value << " " << element.meet << "\n";
        // }
        // cout << "\n";
    }
    graph.clear();

    vector<ll> B(N + 2);
    // index는 N + 1부터 1까지 입력
    // B 입력 -> graph 추가
    for (ll i = N + 1; i > 0; --i) {
        while (graph.size() > 1 && graph[1].meet >= i) graph.pop_front();
        if (i == N + 1) B[i] = 0;
        else if (s[i - 1] != s[i]) B[i] = graph.front().slope * i + graph.front().y_value + (1 - s[i - 1]) * (N + 1 - i);
        else B[i] = B[i + 1];
        if (i != 1 && (i == N + 1 || s[i - 1] != s[i])) {
            Line line = {-s[i - 1], B[i] + s[i - 1] * (N + 1), static_cast<double>(N + 1)};
            while (!graph.empty() && graph.back().meet <= meetPoint(graph.back(), line)) graph.pop_back();
            if (graph.empty()) graph.push_back(line);
            else {
                line.meet = meetPoint(graph.back(), line);
                graph.push_back(line);
            }
        }
        cout << i << "번째" << endl;
        for (Line element: graph) {
            cout << element.slope << " " << element.y_value << " " << element.meet << "\n";
        }
        cout << "\n";
    }

    // for (int i = 0; i < N + 1; ++i) {
    //     cout << A[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 1; i < N + 2; ++i) {
    //     cout << B[i] << " ";
    // }
    // cout << "\n";

    vector<ll> answer(N + 1);
    for (ll i = 0; i < N + 1; ++i) {
        answer[i] = A[i] + B[i + 1];
    }
    cout << *min_element(answer.begin(), answer.end()) << "\n";
    return 0;
}