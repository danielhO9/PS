#include <bits/stdc++.h>
using namespace std;

int N;
set<int> adj[3000];

void dnc(int u, int v, int w, int x) {
    if (v == x) swap(v, u);
    if (w == x) swap(w, u);
    if (abs(v - w) == 1) return;
    if (v > w) swap(v, w);
    for (int i = 0; i < N; ++i) if (adj[v].find(i) != adj[v].end() && adj[w].find(i) != adj[w].end()) {
        int t1 = (v < i && i < w);
        int t2 = (v < u && u < w);
        if (t1 + t2 != 1) continue;
        cout << u + 1 << ' ' << v + 1 << ' ' << w + 1 << ' ' << i + 1 << '\n';
        dnc(u, v, i, u);
        dnc(u, w, i, u);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 3; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for (int i = 0; i < N; ++i) {
        adj[i].insert((i + 1) % N);
        adj[(i + 1) % N].insert(i);
    }
    for (int i = 0; i < N; ++i) if (adj[i].size() == 2) {
        int u = i, v = i + 1, w = i - 1;
        v = v % N;
        w = (w + N) % N;
        cout << u + 1 << ' ' << v + 1 << ' ' << w + 1 << '\n';
        dnc(u, v, w, u);
        return 0;
    }
}