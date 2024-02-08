#include <bits/stdc++.h>
using namespace std;

int C, n, m;
vector<vector<int>> friends(10, vector<int>(0));
int parent, child;
vector<bool> done(10, false);

int solution(vector<bool>& done) {
    int now = 10;
    int answer = 0;
    for (int i = 0; i < n; ++i) if (!done[i]) { now = i; break; }
    if (now == 10) { return 1; }
    for (int possible: friends[now]) {
        if (!done[possible]) {
            done[now] = done[possible] = true;
            answer += solution(done);
            done[now] = done[possible] = false;
        }
    }
    return answer;
}

int main() {
    cin >> C;
    vector<int> result;
    for (int i = 0; i < C; ++i) {
        cin >> n >> m;
        for (int j = 0; j < 10; ++j) friends[j] = vector<int>(0);
        for (int j = 0; j < 10; ++j) done[j] = false;
        for (int j = 0; j < m; ++j) {
            cin >> parent >> child;
            friends[parent].push_back(child);
            friends[child].push_back(parent);
        }
        result.push_back(solution(done));
    }
    for (int element: result) cout << element << "\n";
    return 0;
}