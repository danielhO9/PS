#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAX = 1000000ll * 6000ll;

int T, F, Fu, Fn;
vector<tuple<int, int, ll>> edges;
vector<pair<int, ll>> adj[5001];
ll dis[5001];
bool pos[5001];

void solve() {
    dis[Fu] = 0ll;
    for (int i = 0; i < F - 1; ++i) {
        for (auto [s, e, d]: edges) if (dis[s] != -MAX) {
            dis[e] = max(dis[e], dis[s] + d);
        }
    }
    for (auto [s, e, d]: edges) if (dis[s] != -MAX && dis[e] < dis[s] + d) {
        pos[e] = true;
    }
    queue<int> q;
    for (int i = 1; i <= F; ++i) if (pos[i]) q.push(i);
    while (!q.empty()) {
        int h = q.front(); q.pop();
        for (auto [t, _]: adj[h]) if (!pos[t]) {
            pos[t] = true;
            q.push(t);
        }
    }
    if (dis[Fn] > 0ll || pos[Fn]) cout << "TRUE\n";
    else cout << "FALSE\n";
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> T >> F >> Fu >> Fn;
        if (T == 0) break;
        edges.clear();
        for (int i = 1; i <= F; ++i) pos[i] = false;
        for (int i = 1; i <= F; ++i) dis[i] = -MAX;
        for (int i = 1; i <= F; ++i) adj[i].clear();

        for (int i = 0; i < T; ++i) {
            int s, e; double d; cin >> s >> e >> d;
            d *= 1000.0;
            edges.push_back({s, e, (ll) d});
            adj[s].push_back(make_pair(e, (ll) d));
        }
        solve();
    }

}