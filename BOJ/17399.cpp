#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
vector<pair<int, ll>> adj[MAX_V];
int dep[MAX_V];
ll dis[MAX_V];
vector<vector<int>> f;

void dfs(int v, int p, ll d) {
    f[0][v] = p;
    if (p == -1) {
        dep[v] = 0; dis[v] = 0ll;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [u, nd]: adj[v]) if (u != p) dfs(u, v, nd);
}

int lca(int u, int v) {
	const int h = f.size();
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
	for (int i = 0; i < h; ++i) if ((dif >> i) & 1) {
		u = f[i][u];
	}
    if (u != v) {
        for (int i = h - 1; i >= 0; --i) {
            if (f[i][u] != -1 && f[i][u] != f[i][v]) {
                u = f[i][u]; v = f[i][v];
            }
        }
        u = f[0][u];
    }
    return u;
}

void init() {
	const int h = f.size();
	// root: 1
    dfs(1, -1, 0ll);
	for (int i = 1; i < h; ++i) {
		for (int j = 0; j < MAX_V; ++j) {
			if (f[i - 1][j] == -1) f[i][j] = -1;
			else f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
}

ll getDis(int u, int v) {
	int l = lca(u, v);
	return dis[u] + dis[v] - dis[l] * 2;
}

void query() {
	const int h = f.size();
	vector<int> v(3); for (int i = 0; i < 3; ++i) cin >> v[i];
	for (int i = 0; i < 3; ++i) {
		int j = (i + 1) % 3;
		int a = v[i], b = v[j], c = v[(i + 2) % 3];
		int d = getDis(a, b);
		if (d % 2) continue;
		if (dep[a] < dep[b]) swap(a, b);
		int dif = d / 2;
		for (int k = 0; k < h; ++k) if ((dif >> k) & 1) {
			a = f[k][a];
		}
		if (getDis(a, c) == dif) {
			cout << a << '\n';
			return;
		}
	}
	cout << -1 << '\n';
}

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int X, Y; cin >> X >> Y;
		adj[X].push_back({Y, 1});
		adj[Y].push_back({X, 1});
	}
	int h = (int)ceil(log2(MAX_V)); ++h;
	f = vector<vector<int>>(h, vector<int>(MAX_V));
	init();
	int Q; cin >> Q;
	while (Q--) {
		query();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}