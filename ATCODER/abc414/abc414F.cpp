#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    ll u, v, idx;
};

ll N, K;
vector<Edge> adj[200001];
vector<Edge> inv[200001];
ll cache[400000][20], cnt[200001][20];

void solve() {
    cin >> N >> K;
    for (ll i = 1; i <= N; ++i) {
        adj[i].clear();
        inv[i].clear();
    }
    ll num = 0;
    for (ll i = 0; i < N - 1; ++i) {
        ll u, v; cin >> u >> v;
        inv[v].push_back(Edge {u, v, num});
        adj[u].push_back(Edge {u, v, num++});
        inv[u].push_back(Edge {v, u, num});
        adj[v].push_back(Edge {v, u, num++});
    }
    for (ll i = 0; i <= num; ++i) for (ll j = 0; j < K; ++j) cache[i][j] = INT32_MAX;
    for (int i = 1; i <= N; ++i) for (int j = 0; j < K; ++j) cnt[i][j] = 0;
    queue<pair<Edge, ll>> q;
    q.push(make_pair(Edge {N+1, 1, num}, 0));
    cache[num][0] = 0;
    while (!q.empty()) {
        auto [he, k] = q.front(); q.pop();
        if (cnt[he.v][k] == 2) continue;
        ++cnt[he.v][k];
        for (auto edge: adj[he.v]) if (k == 0 || he.u != edge.v) {
            if (cache[edge.idx][(k + 1) % K] > cache[he.idx][k] + 1) {
                q.push(make_pair(edge, (k + 1) % K));
                cache[edge.idx][(k + 1) % K] = cache[he.idx][k] + 1;
            }
        }
    }
    for (ll i = 2; i <= N; ++i) {
        ll ans = INT32_MAX;
        for (auto e: inv[i]) ans = min(ans, cache[e.idx][0]);
        if (ans == INT32_MAX) cout << -1 << ' ';
        else cout << ans / K << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t; cin >> t;
    while (t--) solve();
}