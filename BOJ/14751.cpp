#include <bits/stdc++.h>

using namespace std;
using ld = long double;

struct Line {
    int index; ld slope; ld y_value; ld meet;

    bool operator < (const Line& var) const {
        if (abs(slope - var.slope) < 1e-10) {return y_value < var.y_value;}
		return slope < var.slope;
	}
};

ld meetPoint(Line& line1, Line& line2) {
    return (line2.y_value - line1.y_value) / (line1.slope - line2.slope);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ld maxY, minY; int n;
    cin >> maxY >> minY; cin >> n;

    vector<Line> sorter;
    for (int i = 0; i < n; i++) {
        ld upperX, lowX; cin >> upperX >> lowX;
        sorter.push_back({i + 1, (lowX - upperX) / (maxY - minY), -lowX, 0});
    }

    sort(sorter.begin(), sorter.end());

    vector<Line> graph;
    for (int i = 0; i < n; ++i) {
        Line line = sorter[i];
        while (!graph.empty() && abs(graph.back().slope - line.slope) < 1e-10) {
            graph.pop_back();
        }
        while (!graph.empty() && graph.back().meet >= meetPoint(line, graph.back())) {
            graph.pop_back();
        }
        if (graph.empty()) {
            line.meet = 0.0;
            graph.push_back(line);
        }
        else {
            line.meet = meetPoint(line, graph.back());
            graph.push_back(line);
        }
    }

    int m; cin >> m;
    vector<int> answer(m);
    for (int i = 0; i < m; ++i) {
        ld question, temp; cin >> temp; question = temp - minY;
        int start = 0, end = graph.size() - 1;
        int mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
        while (start < end) {
            if (question - graph[mid].meet > -1e-10) start = mid;
            else end = mid - 1;
            mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
        }
        answer[i] = graph[mid].index;
    }
    for (int i = 0; i < m; ++i) {
        cout << answer[i] << "\n";
    }
}