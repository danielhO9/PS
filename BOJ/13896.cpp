#include <bits/stdc++.h>
using namespace std;

int N, Q, R;
vector<int> adj[100005];
int sz[100005];
int dep[100005];
int f[100005][19];

void dfs(int v, int p) {
	sz[v] = 1;
	f[v][0] = p;
	for (auto u: adj[v]) if (u != p) {
		dep[u] = dep[v] + 1;
		dfs(u, v);
		sz[v] += sz[u];
	}
}

void init() {
	for (int i = 1; i < 19; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (f[j][i - 1] != -1) f[j][i] = f[f[j][i - 1]][i - 1];
			else f[j][i] = -1;
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int dif = dep[u] - dep[v];
	for (int i = 0; i < 19; ++i) if ((dif >> i) & 1) u = f[u][i];
	if (u != v) {
		for (int i = 18; i >= 0; --i) {
			if (f[u][i] != f[v][i]) {
				u = f[u][i], v = f[v][i];
			}
		}
		u = f[u][0];
	}
	return u;
}

int prv(int u, int v) {
	int dif = dep[u] - dep[v] - 1;
	for (int i = 0; i < 19; ++i) if ((dif >> i) & 1) u = f[u][i];
	return u;
}

void solve() {
	cin >> N >> Q >> R;
	for (int i = 1; i <= N; ++i) {
		adj[i].clear();
		sz[i] = 1;
		f[i][0] = -1;
		dep[i] = 0;
	}
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dep[1] = 0; dfs(1, -1);
	init();
	for (int i = 0; i < Q; ++i) {
		int S, U; cin >> S >> U;
		if (S == 0) R = U;
		else {
			int p = lca(U, R);
			if (U == R) {
				cout << N << '\n';
			} else if (p == U) {
				int pprv = prv(R, U);
				cout << N - sz[pprv] << '\n';
			} else {
				cout << sz[U] << '\n';
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ":\n";
		solve();
	}
}