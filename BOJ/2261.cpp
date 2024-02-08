#include <bits/stdc++.h>
using namespace std;

bool compareY(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second == b.second) return a.first <= b.first;
    return a.second < b.second;
}

int n; vector<pair<int, int>> points;

int dis(int a, int b) { return (points[a].first - points[b].first) * (points[a].first - points[b].first) + (points[a].second - points[b].second) * (points[a].second - points[b].second); }

int solution(int left, int right) {
    if (right - left == 1) return dis(left, right);
    if (right - left == 2) return min({dis(left, left + 1), dis(left, left + 2), dis(left + 1, left + 2)});

    int mid = (left + right) / 2;
    int ret = min(solution(left, mid), solution(mid + 1, right));
    int midX = (points[mid].first + points[mid + 1].first) / 2;
    vector<pair<int, int>> temp;
    for (int i = left; i <= right; ++i) {if ((points[i].first - midX) * (points[i].first - midX) < ret) temp.push_back(points[i]); }
    sort(temp.begin(), temp.end(), compareY);
    // for (pair<int, int> a: temp) cout << a.first << " " << a.second << endl;
    for (int i = 0; i + 1 < temp.size(); ++i) {
        for (int j = i + 1; j < temp.size(); ++j) {
            if ((temp[i].second - temp[j].second) * (temp[i].second - temp[j].second) >= ret) break;
            ret = min(ret, (temp[i].first - temp[j].first) * (temp[i].first - temp[j].first) + (temp[i].second - temp[j].second) * (temp[i].second - temp[j].second));
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n; int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        points.push_back({a, b});
    }
    sort(points.begin(), points.end());
    cout << solution(0, n - 1);
    return 0;
}