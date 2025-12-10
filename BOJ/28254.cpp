#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
vector<pair<int, int>> adj[500001];
unordered_map<int, ll> flag[500001];
ll cnt[500000];
ll val[500001];
ll ans[500000];

void dfs(int v, int p, int idx) {
    for (auto [u, iidx]: adj[v]) if (u != p) {
        dfs(u, v, iidx);
        if (flag[u].size() > flag[v].size()) {
            swap(flag[u], flag[v]);
            swap(val[u], val[v]);
        }
        for (auto [i, j]: flag[u]) {
            val[v] += j * (cnt[i] - 2ll * flag[v][i] - j);
            flag[v][i] += j;
        }
    }
    if (idx >= 0) ans[idx] = val[v];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
    }
    for (int i = 0; i < M; ++i) {
        cin >> cnt[i];
        for (int j = 0; j < cnt[i]; ++j) {
            int v; cin >> v;
            flag[v][i] = 1;
            val[v] += cnt[i] - 1;
        }
    }
    dfs(1, 0, -1);
    for (int i = 0; i < N - 1; ++i) cout << ans[i] << '\n';
}