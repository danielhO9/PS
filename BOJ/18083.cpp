#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
		return slope > var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) { return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope); }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = static_cast<double>(LLONG_MAX); return false; }
        a->meet = meetPoint(a, next(a));
        return a->meet > next(a)->meet;
    }

    void add(ll slope, ll y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }

};

vector<bool> visited(2001, false);
vector<vector<pair<ll, ll>>> graph(2001);
vector<vector<vector<pair<ll, ll>>>> dp(2001, vector<vector<pair<ll, ll>>>(2001, vector<pair<ll, ll>>(0)));
vector<vector<bool>> startPoint(2001, vector<bool>(2001, false));

void solution(ll i, ll x) {
    if (startPoint[i][x]) return;
    visited[x] = true;
    startPoint[i][x] = true;
    if (i == 1) return;
    for (pair<ll, ll> element: dp[i][x]) solution(i - 1, element.second);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll n; int m; cin >> n >> m;
    ll a, b; ll l;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> l;
        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
        if (a == 1 || b == 1) {
            if (dp[1][a + b - 1].empty() || dp[1][a + b - 1].front().first == l) dp[1][a + b - 1].push_back({l, 1});
            else if (dp[1][a + b - 1].front().first > l) dp[1][a + b - 1] = {{l, 1}};
        }
    }
    LineContainer lines;
    for (int i = 2; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            // dp[i - 1][j] => dp[i][elemnt.first]
            if (!dp[i - 1][j].empty()) {
                for (pair<ll, ll> element: graph[j]) {
                    if (dp[i][element.first].empty() || dp[i][element.first].front().first == element.second + dp[i - 1][j].front().first) dp[i][element.first].push_back({element.second + dp[i - 1][j].front().first, j});
                    else if (dp[i][element.first].front().first > element.second + dp[i - 1][j].front().first) dp[i][element.first] = {{element.second + dp[i - 1][j].front().first, j}};
                }
            }
        }
    }
    visited[n] = true; visited[1] = true;
    ll temp; int cnt;
    for (int i = 1; i < n + 1; ++i) if (!dp[i][n].empty()) {
        lines.add(i, dp[i][n].front().first);
        // cout << i << " " << dp[i][n].front().first << endl;
    }
    for (Line element: lines) {
        if (element.meet >= 0) solution(element.slope, n);
    }
    // cout << endl;
    // for (Line element: lines) cout << element.slope << " " << element.y_value << " " << element.meet << endl;
    // for (int i = 1; i < n + 1; ++i) {
    //     for (int j = 1; j < n + 1; ++j) {
    //         if (!dp[i][j].empty()) {
    //             for (pair<ll, ll> element: dp[i][j]) cout << i << "," << j << ":" << element.first << " " << element.second << "  ";
    //         }
    //     }
    //     cout << endl;
    // }
    int answer = 0;
    for (int i = 1; i <= n; ++i) if (!visited[i]) answer++;
    if (answer != 0) { cout << answer << "\n"; for (int i = 1; i <= n; ++i) if (!visited[i]) cout << i << " "; }
    else cout << 0;
    return 0;
}