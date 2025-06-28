#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 0-index
struct UF {
	vector<ll> par, sz, val;
    vector<vector<int>> adj;
    int cur;
    UF() {}
	UF(int n) {
		par.resize(n * 2);
		sz.resize(n * 2);
        adj.resize(n * 2);
        val.resize(n * 2);
        for (int i = 1; i < 2 * n; ++i) par[i] = i;
        for (int i = 1; i <= n; ++i) sz[i] = 1;
        for (int i = n + 1; i < 2 * n; ++i) sz[i] = 0;
        cur = n + 1;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_path(int x, int y) {
		x = find(x); y = find(y);
        sz[cur] = sz[x] + sz[y];

        par[x] = cur;
        par[y] = cur;

        adj[x].push_back(cur);
        adj[y].push_back(cur);
        adj[cur].push_back(x);
        adj[cur].push_back(y);
        ++cur;
	}
};

int n, m;
ll ans[200000];
UF uf;

void dfs(int v, int p) {
    uf.val[v] += uf.val[p];
    for (int u: uf.adj[v]) if (u != p) {
        dfs(u, v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    uf = UF {n};
    for (int i = 0; i < m; ++i) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) uf.union_path(x, y);
        else {
            ans[x] -= y;
            x = uf.find(x);
            ll sz = uf.sz[x];
            uf.val[x] += y / sz;
        }
    }
    int rt = uf.find(1);
    dfs(rt, 0);
    for (int i = 1; i <= n; ++i) ans[i] += uf.val[i];
    int cnt = 0;
    for (int i = 2; i <= n; ++i) if (ans[i] != 0) ++cnt;
    cout << cnt << '\n';
    for (int i = 2; i <= n; ++i) if (ans[i] != 0) {
        if (ans[i] > 0) cout << i << ' ' << 1 << ' ' << ans[i] << '\n';
        else cout << 1 << ' ' << i << ' ' << -ans[i] << '\n';
    }
}