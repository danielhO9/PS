#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> adj[101];
bool vis[101];
int deg[101];
int cnt[101];

void dfs(int v) {
    if (vis[v]) return;
    vis[v] = true;
    for (auto [u, _]: adj[v]) {
        ++deg[u];
        dfs(u);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int X, Y, K; cin >> X >> Y >> K;
        adj[X].push_back(make_pair(Y, K));
    }
    dfs(N);
    queue<int> q; q.push(N);
    cnt[N] = 1;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto [u, c]: adj[v]) {
            --deg[u];
            cnt[u] += c * cnt[v];
            if (deg[u] == 0) q.push(u);
        }
    }
    for (int i = 1; i <= N; ++i) if (adj[i].empty() && cnt[i] != 0) {
        cout << i << ' ' << cnt[i] << '\n';
    }
}