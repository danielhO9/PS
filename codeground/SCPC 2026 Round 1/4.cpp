#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct Edge {
    int a, b;
    ll w, d;
};

int N, M, s, t;
Edge edges[200001];
ll dis[200001];
const ll MAX = 2e15;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) cin >> edges[i].a >> edges[i].b;
    for (int i = 0; i < M; ++i) cin >> edges[i].w >> edges[i].d;
    cin >> s >> t;
    sort(edges, edges + M, [](const auto& l, const auto& r) {
        return l.d < r.d;
    });
    for (int i = 1; i <= N; ++i) dis[i] = MAX;
    dis[s] = 0;
    for (int i = 0; i < M; ++i) {
        auto edge = edges[i];
        ll na = dis[edge.b] + edge.w;
        dis[edge.b] = min(dis[edge.b], dis[edge.a] + edge.w);
        dis[edge.a] = min(dis[edge.a], na);
    }
    if (dis[t] == MAX) cout << -1 << '\n';
    else cout << dis[t] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i <<  '\n';
        solve();
        cout.flush();
    }
}