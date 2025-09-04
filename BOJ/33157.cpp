#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<int, __int128_t>> adj[200001];
__int128_t sz[200001], sm[200001], sqsm[200001], val[200001];

void dfs(int v, int p) {
    sz[v] = 1;
    for (auto [u, d]: adj[v]) if (u != p) {
        dfs(u, v);
        sz[v] += sz[u];
        sm[v] += sm[u] + sz[u] * d;
        sqsm[v] += sqsm[u] + sm[u] * 2 * d + d * d * sz[u];
    }
}

void dfs2(int v, int p) {
    val[v] = sqsm[v] * N - sm[v] * sm[v];
    __int128_t vsz = sz[v], vsm = sm[v], vsqsm = sqsm[v];
    for (auto [u, d]: adj[v]) if (u != p) {
        __int128_t usz = sz[u], usm = sm[u], usqsm = sqsm[u];
        sz[v] = N - usz; sm[v] = vsm - (usm + usz * d); sqsm[v] = vsqsm - (usqsm + usm * 2 * d + d * d * usz);
        sz[u] = N; sm[u] += sm[v] + sz[v] * d; sqsm[u] += sqsm[v] + sm[v] * 2 * d + d * d * sz[v];
        dfs2(u, v);
        sz[v] = vsz; sm[v] = vsm; sqsm[v] = vsqsm;
        sz[u] = usz; sm[u] = usm; sqsm[u] = usqsm;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    dfs(1, 0);
    dfs2(1, 0);
    __int128_t mn = val[1];
    for (int i = 1; i <= N; ++i) mn = min(mn, val[i]);
    for (int i = 1; i <= N; ++i) if (val[i] == mn) {
        cout << i;
        return 0;
    }
}