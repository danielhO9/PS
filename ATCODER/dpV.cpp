#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N; ll M;
vector<int> adj[100001];
ll down[100001];
ll ans[100001];

void dfs1(int v, int p) {
	down[v] = 1;
	for (auto u: adj[v]) if (u != p) {
		dfs1(u, v);
		down[v] *= (down[u] + 1) % M;
		down[v] %= M;
	}
}

void dfs2(int v, int p) {
	ans[v] = down[v];
	ll prvv = down[v];

	unordered_map<int, int> m;
	vector<ll> ds;
	int cnt = 0;
	for (auto u: adj[v]) {
		ds.push_back((down[u] + 1) % M);
		m[u] = cnt++;
	}
	int sqrt_sz = sqrt(cnt);
	sqrt_sz = max(sqrt_sz, 1);

	vector<ll> sqrt_ds(((cnt - 1) / sqrt_sz) + 1, 1);
	for (int i = 0; i < cnt; ++i) {
		sqrt_ds[i / sqrt_sz] *= ds[i];
		sqrt_ds[i / sqrt_sz] %= M;
	}
	for (auto u: adj[v]) if (u != p) {
		int idx = m[u];
		ll val = 1;
		int ord = idx / sqrt_sz;
		for (int i = 0; i < sqrt_ds.size(); ++i) if (i != ord) {
			val *= sqrt_ds[i];
			val %= M;
		}
		for (int i = ord * sqrt_sz; i < min((ord + 1) * sqrt_sz, cnt); ++i) if (i != idx) {
			val *= ds[i];
			val %= M;
		}
		down[v] = val;

		val = 1;
		for (auto w: adj[u]) {
			val *= (down[w] + 1) % M;
			val %= M;
		}
		ll prvu = down[u];
		down[u] = val;
		dfs2(u, v);

		down[v] = prvv;
		down[u] = prvu;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N - 1; ++i) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= N; ++i) cout << ans[i] << '\n';
}