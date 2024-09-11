#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, Q;
vector<ll> adj[100001];
ll x[100001];
ll par[100001];

void dfs(int v, int p) {
	par[v] = p;
	for (auto u: adj[v]) if (u != p) dfs(u, v);
}

void query(ll v, ll X) {
	if (X <= x[v]) {
		x[v] += X;
		return;
	}
	int cnt = 0;
	for (auto u: adj[v]) if (u != par[v]) ++cnt;
	X -= x[v];
	x[v] *= 2;
	if (cnt == 0) return;
	X /= cnt;
	for (auto u: adj[v]) if (u != par[v]) query(u, X);
}

void solve() {
	cin >> N >> Q;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) cin >> x[i];
	dfs(1, 0);
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			int u; ll X; cin >> u >> X;
			query(u, X);
		} else {
			int u; cin >> u;
			cout << x[u] << "\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}