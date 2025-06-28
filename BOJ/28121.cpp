#include <bits/stdc++.h>
using namespace std;

// 0-index
struct UF {
	vector<int> par, sz;
    vector<vector<int>> v;

	UF(int _sz) {
		par.resize(_sz);
		sz.resize(_sz);
        v.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
		for (int i = 0; i < _sz; ++i) sz[i] = 1;
        for (int i = 0; i < _sz; ++i) v[i].push_back(i);
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
        for (int i: v[x]) v[y].push_back(i);
	}
};

int N, Q;
int col[300001];
bool tar[300001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    vector<pair<int, int>> edge;
    for (int i = 0; i < Q; ++i) {
        int u, v; cin >> u >> v;
        edge.push_back(make_pair(u, v));
    }
    UF uf {N + 1};
    int ans = 0;
    for (auto [u, v]: edge) {
        if (uf.find(u) == uf.find(v)) {
            int p = uf.find(u);
            if (col[u] == col[v] && !tar[p]) {
                tar[p] = true;
                ans += uf.sz[p];
            }
        } else {
            if (col[u] && col[v]) {
                int pu = uf.find(u);
                int pv = uf.find(v);
                if (tar[pu] && !tar[pv]) ans += uf.sz[pv];
                if (tar[pv] && !tar[pu]) ans += uf.sz[pu];
                if (col[u] == col[v]) {
                    if (uf.v[pu].size() < uf.v[pv].size()) {
                        for (int i: uf.v[pu]) col[i] = 3 - col[i];
                    } else {
                        for (int i: uf.v[pv]) col[i] = 3 - col[i];
                    }
                }
            } else if (col[u]) {
                col[v] = 3 - col[u];
                if (tar[uf.find(u)]) ++ans;
            } else if (col[v]) {
                col[u] = 3 - col[v];
                if (tar[uf.find(v)]) ++ans;
            } else {
                col[u] = 1;
                col[v] = 2;
            }
            bool flag = false;
            if (tar[uf.find(u)] || tar[uf.find(v)]) flag = true;
            uf.union_path(u, v);
            if (flag) tar[uf.find(u)] = true;
        }
        cout << ans << '\n';
    }

}