#include <bits/stdc++.h>
using namespace std;

// 0-index
struct UF {
	vector<int> par, sz;

	UF(int _sz) {
		par.resize(_sz);
		sz.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
		for (int i = 0; i < _sz; ++i) sz[i] = 1;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_path(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);
		par[x] = y;
		sz[y] += sz[x];
	}
};

int n, m;
vector<int> adj[1001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    UF uf {n + 1};
    for (int i = 0; i < m; ++i) {
        char c; int p, q; cin >> c >> p >> q;
        if (c == 'E') {
            adj[p].push_back(q);
            adj[q].push_back(p);
        } else {
            uf.union_path(p, q);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j + 1 < adj[i].size(); ++j) {
            uf.union_path(adj[i][j], adj[i][j + 1]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) if (uf.find(i) == i) ++ans;
    cout << ans;
}