#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
int adj[8][8];
int deg[8];
vector<pair<int, int>> edges;
vector<int> cur;
int ans;

void f() {
    if (cur.size() == N) {
        for (int i = 0; i < N; ++i) if (deg[i] != 2) return;
        int cnt = 0;
        for (auto i: cur) {
            auto [u, v] = edges[i];
            if (adj[u][v]) ++cnt;
        }
        ans = min(ans, N + M - 2 * cnt);
        return;
    }
    int last;
    if (cur.empty()) last = -1;
    else last = cur.back();
    for (int i = last + 1; i < edges.size(); ++i) {
        cur.push_back(i);
        auto [u, v] = edges[i];
        ++deg[u]; ++deg[v];
        if (deg[u] <= 2 && deg[v] <= 2) f();
        --deg[u]; --deg[v];
        cur.pop_back();
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int A, B; cin >> A >> B; --A; --B;
        adj[A][B] = 1;
        adj[B][A] = 1;
    }
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) edges.push_back(make_pair(i, j));
    ans = INT32_MAX;
    f();
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}