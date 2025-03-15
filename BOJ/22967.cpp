#include <bits/stdc++.h>
using namespace std;

int N;
bool adj[301][301];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u][v] = true;
        adj[v][u] = true;
    }
    if (N <= 4) {
        cout << N * (N - 1) / 2 - (N - 1) << '\n';
        cout << 1 << "\n";
        for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) if (!adj[i][j]) cout << i << ' ' << j << '\n';
    } else {
        int cnt = 0;
        for (int i = 2; i <= N; ++i) if (!adj[1][i]) ++cnt;
        cout << cnt << '\n';
        cout << 2 << '\n';
        for (int i = 2; i <= N; ++i) if (!adj[1][i]) cout << 1 << ' ' << i << '\n';
    }
}