#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
vector<vector<ld>> tlschs, dksdka;
int n, m;

ld pointToLine(ld x, ld y, const vector<ld>& a) {
    ld dist;
    // 점직거를 사용할 수 있는지 판별
    if ((x - a[0]) * (a[2] - a[0]) + (y - a[1]) * (a[3] - a[1]) > 0
    && (x - a[2]) * (a[0] - a[2]) + (y - a[3]) * (a[1] - a[3]) > 0) {
        if (abs(a[0] - a[2]) < 1e-12) dist = abs(x - a[0]);
        else {
            ld m = (a[3] - a[1]) / (a[2] - a[0]);
            ld n = a[1] - a[0] * m;
            dist = abs(m * x - y + n) / sqrt(m * m + 1);
        }
    } else {
        dist = min(sqrt((a[0] - x) * (a[0] - x) + (a[1] - y) * (a[1] - y)),
        sqrt((a[2] - x) * (a[2] - x) + (a[3] - y) * (a[3] - y)));
    }
    return dist;
}
vector<ld> tempAnswer;
ld solution(const vector<ld>& a, const vector<ld>& b) {
    tempAnswer.clear(); tempAnswer.shrink_to_fit();
    tempAnswer.push_back(pointToLine(a[0], a[1], b));
    tempAnswer.push_back(pointToLine(a[2], a[3], b));
    tempAnswer.push_back(pointToLine(b[0], b[1], a));
    tempAnswer.push_back(pointToLine(b[2], b[3], a));
    return *min_element(tempAnswer.begin(), tempAnswer.end());
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m; ld x1, y1, x2, y2;
    ld answer = 40000.0;
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        tlschs.push_back({x1, y1, x2, y2});
    }
    for (int i = 0; i < m; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        dksdka.push_back({x1, y1, x2, y2});
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            answer = min(answer, solution(tlschs[i], dksdka[j]));
        }
    }
    cout << fixed;
    cout.precision(9);
    cout << answer;
    return 0;
}