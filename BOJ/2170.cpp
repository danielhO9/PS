#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<pair<int, int>> lines;
    int a, b;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        lines.push_back({a, b});
    }
    sort(lines.begin(), lines.end());
    int answer = 0;
    pair<int, int> now = {-2e9, -2e9};
    for (pair<int, int> line: lines) {
        if (now.second < line.first) {
            answer += now.second - now.first; 
            now.first = line.first; now.second = line.second;
        } else if (now.second < line.second) now.second = line.second;
    }
    answer += now.second - now.first;
    cout << answer;
    return 0;
}