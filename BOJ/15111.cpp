#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line { ll slope, y_value; double meet;};

struct flight { ll a, b, s, e; };

vector<flight> dictionary; ll timeline[1000001];

double meetPoint(Line& line1, Line& line2) {
    return (line2.y_value - line1.y_value) / static_cast<double>(line1.slope - line2.slope);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll n, m; cin >> n >> m;
    dictionary.push_back({-1, -1, -1, -1});
    ll dp[m + 1]; deque<Line> linecontainer[n + 1];
    vector<ll> answer;

    ll a, b, s, e;
    for (ll i = 1; i <= m; ++i) {
        cin >> a >> b >> s >> e;
        dictionary.push_back({a, b, s, e});
        timeline[s] = i; timeline[e] = i;
    }

    for (ll t = 0; t <= 1000000; ++t) {
        if (timeline[t] == 0) continue;
        if (dictionary[timeline[t]].s == t) {
            // dictionary[timeline[t]].a
            if (linecontainer[dictionary[timeline[t]].a].empty()) {
                if (dictionary[timeline[t]].a == 1) dp[timeline[t]] = t * t;
                else {
                    dp[timeline[t]] = -1;
                    continue;
                }
            }
            else {
                while (linecontainer[dictionary[timeline[t]].a].front().meet <= t) linecontainer[dictionary[timeline[t]].a].pop_front();
                dp[timeline[t]] = linecontainer[dictionary[timeline[t]].a].front().slope * t + linecontainer[dictionary[timeline[t]].a].front().y_value + t * t;
            }
            if (dictionary[timeline[t]].b == n) answer.push_back(dp[timeline[t]]);
        }
        if (dictionary[timeline[t]].e == t) {
            if (dp[timeline[t]] == -1) continue;
            // dictionary[timeline[t]].a
            Line line = {(-2) * dictionary[timeline[t]].e, dp[timeline[t]] + dictionary[timeline[t]].e * dictionary[timeline[t]].e, 1000001};
            while (linecontainer[dictionary[timeline[t]].b].size() >= 2 && linecontainer[dictionary[timeline[t]].b][linecontainer[dictionary[timeline[t]].b].size()-2].meet >= meetPoint(linecontainer[dictionary[timeline[t]].b].back(), line)) linecontainer[dictionary[timeline[t]].b].pop_back();
            if (linecontainer[dictionary[timeline[t]].b].empty()) linecontainer[dictionary[timeline[t]].b].push_back(line);
            else {
                linecontainer[dictionary[timeline[t]].b].back().meet = meetPoint(linecontainer[dictionary[timeline[t]].b].back(), line);
                linecontainer[dictionary[timeline[t]].b].push_back(line);
            }
        }
    }
    cout << *min_element(answer.begin(), answer.end()) << "\n";
}