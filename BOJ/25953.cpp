#include <bits/stdc++.h>
using namespace std;

int n, t, m, s, e;
int cache[10000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> t >> m >> s >> e;
    memset(cache, -1, sizeof(cache));
    cache[s] = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < m; ++j) {
            int u, v, w; cin >> u >> v >> w;
            if (cache[u] != -1) q.push(make_pair(v, cache[u] + w));
            if (cache[v] != -1) q.push(make_pair(u, cache[v] + w));
        }
        while (!q.empty()) {
            auto [v, w] = q.front(); q.pop();
            if (cache[v] == -1) cache[v] = w;
            else cache[v] = min(cache[v], w);
        }
    }
    cout << cache[e];
}