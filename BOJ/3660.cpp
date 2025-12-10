#include <bits/stdc++.h>
using namespace std;
const double MAX = 7e5;

struct Edge {
    int s, e, m, t, p, d;
};

string s, e;
map<string, int> ma;
int n, cnt;
vector<Edge> adj[2000];
double dis[2000][60];

void solve() {
    ma.clear();
    cnt = 0;

    cin >> s >> e;
    if (ma.find(s) == ma.end()) ma[s] = cnt++;
    if (ma.find(e) == ma.end()) ma[e] = cnt++;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        string ss, ee; cin >> ss >> ee;
        if (ma.find(ss) == ma.end()) ma[ss] = cnt++;
        if (ma.find(ee) == ma.end()) ma[ee] = cnt++;
        int m, t, p, d; cin >> m >> t >> p >> d;
        adj[ma[ee]].push_back(Edge {ma[ss], ma[ee], m, t, p, d});
    }

    for (int i = 0; i < cnt; ++i) for (int j = 0; j < 60; ++j) dis[i][j] = MAX;
    for (int i = 0; i < 60; ++i) dis[1][i] = 0.0;
    queue<int> q; q.push(1);
    vector<bool> inq(cnt); inq[1] = true;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        inq[v] = false;

        for (int j = 120; j >= 0; --j) {
            dis[v][j % 60] = min(dis[v][j % 60], dis[v][(j + 1) % 60] + 1);
        }

        for (const auto& e: adj[v]) {
            // cout << e.s << ' ' << e.e << '\n';
            double tmp = 0.0;
            int arr = (e.m + e.t) % 60;
            tmp += 0.01 * (100 - e.p) * (dis[e.e][arr] + e.t);
            for (int i = 1; i <= e.d; ++i) {
                ++arr; arr %= 60;
                tmp += 0.01 * e.p / e.d * (dis[e.e][arr] + e.t + i);
            }
            if (dis[e.s][e.m] - tmp > 1e-8) {
                dis[e.s][e.m] = tmp;
                if (!inq[e.s]) {
                    inq[e.s] = true;
                    q.push(e.s);
                }
                // cout << e.s << '\n';
            }
        }
    }

    double mn = MAX;
    for (int i = 0; i < 60; ++i) mn = min(mn, dis[0][i]);
    if (mn > 6e5) cout << "IMPOSSIBLE\n";
    else {
        cout.precision(7);
        cout << fixed;
        cout << mn << '\n';
    }

    for (int i = 0; i < cnt; ++i) adj[i].clear();

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}