#include <bits/stdc++.h>
using namespace std;

struct UF {
	int sz;
	vector<int> par;

	void init(int _sz) {
		sz = _sz;
		par.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		par[x] = y;
	}
};

vector<int> adj[200001];
int n, m1, m2;

void solve() {
	cin >> n >> m1 >> m2;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < m1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	UF uf; uf.init(n + 1);
	for (int i = 0; i < m2; ++i) {
		int u, v; cin >> u >> v;
		uf.union_path(u, v);
	}
	

	UF nuf; nuf.init(n + 1);
	int cut = 0;
	for (int i = 1; i <= n; ++i) {
		int p = uf.find(i);
		for (auto j: adj[i]) {
			if (p != uf.find(j)) {
				if (j > i) ++cut;
			} else {
				nuf.union_path(i, j);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (nuf.find(uf.find(i)) != nuf.find(i)) {
			nuf.union_path(uf.find(i), i);
			++cut;
		}
	}
	// cout << cut << '\n';
	// for (int i = 1; i <= n; ++i) if (sz[i] > 0) cut += sz[i] - 1;
	cout << cut << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}