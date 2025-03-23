#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 200001;
vector<vector<pair<int, ll>>> adj;

struct LCA {
    int N;
    vector<vector<int>> f;
    vector<vector<pair<int, ll>>> adj;
    vector<int> dep;
    vector<ll> dis;

    void dfs(int v, int p, ll d) {
        f[0][v] = p;
        if (p == -1) {
            dep[v] = 0; dis[v] = 0ll;
        } else {
            dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
        }
        for (auto [u, nd]: adj[v]) if (u != p) dfs(u, v, nd);
    }

    void init() {
        const int h = f.size();
        dfs(1, -1, 0ll); // root: 1
        for (int i = 1; i < h; ++i) {
            for (int j = 0; j < N; ++j) {
                if (f[i - 1][j] == -1) f[i][j] = -1;
                else f[i][j] = f[i - 1][f[i - 1][j]];
            }
        }
    }

    LCA(vector<vector<pair<int, ll>>>& _adj) : adj(_adj) {
        N = adj.size();
        dep.resize(N);
        dis.resize(N);
        int h = (int)ceil(log2(N)); ++h;
        f = vector<vector<int>>(h, vector<int>(N));
        init();
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

    ll getDis(int u, int v) {
        int l = lca(u, v);
        return dis[u] + dis[v] - dis[l] * 2;
    }
};

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

int N;

struct Edge {
    int s, e;
    ll d;
};

int s, e;
ll d;

void solve() {
	cin >> N;
    adj.resize(N + 1);
    vector<Edge> es;
    UF uf; uf.init(N + 1);
    for (int i = 0; i < N; ++i) {
        int u, v; ll c; cin >> u >> v >> c;
        if (uf.find(u) == uf.find(v)) {
            s = u, e = v, d = c;
        } else {
            uf.union_path(u, v);
            es.push_back({u, v, c});
        }
    }
    for (auto i: es) adj[i.s].push_back({i.e, i.d}), adj[i.e].push_back({i.s, i.d});
    LCA lca(adj);
    
    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        ll ans = lca.getDis(u, v);
        ans = min(ans, lca.getDis(u, s) + lca.getDis(v, e) + d);
        ans = min(ans, lca.getDis(u, e) + lca.getDis(v, s) + d);
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}