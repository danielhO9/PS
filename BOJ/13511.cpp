#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfs(int v, int p, ll d, vector<vector<int>>& f, vector<int>& dep, vector<ll>& dist, vector<vector<pair<int, ll>>>& adj) {
    f[0][v] = p;
    if (p == -1) {
        dep[v] = 0; dist[v] = 0ll;
    } else {
        dep[v] = dep[p] + 1; dist[v] = dist[p] + d;
    }
    for (auto [u, nd]: adj[v]) if (u != p) dfs(u, v, nd, f, dep, dist, adj);
}

int lca(int u, int v, vector<int>& dep, int& h, vector<vector<int>>& f) {
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

void init(int& V, vector<vector<pair<int, ll>>>& adj, vector<int>& dep, vector<ll>& dist, int& h, vector<vector<int>>& f) {
	// root: 1
    dfs(1, -1, 0ll, f, dep, dist, adj);
	for (int i = 1; i < h; ++i) {
		// 시작점, 끝점 조절
		for (int j = 1; j <= V; ++j) {
			if (f[i - 1][j] == -1) f[i][j] = -1;
			else f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
}

ll distance(int u, int v, vector<int>& dep, vector<ll>& dist, int& h, vector<vector<int>>& f) {
	int l = lca(u, v, dep, h, f);
	return dist[u] + dist[v] - dist[l] * 2;
}

int query(int u, int v, int k, vector<int>& dep, int& h, vector<vector<int>>& f) {
	--k;
	int l = lca(u, v, dep, h, f);
	if (k <= dep[u] - dep[l]) {
		for (int i = 0; i < h; ++i) if ((k >> i) & 1) {
			u = f[i][u];
		}
		return u;
	}
	
	k = dep[v] - (dep[l] + k - (dep[u] - dep[l]));
	for (int i = 0; i < h; ++i) if ((k >> i) & 1) {
		v = f[i][v];
	}
	return v;
}

void solve() {
	// max vertex number
	int N; cin >> N;
	vector<vector<pair<int, ll>>> adj(N + 1);
	for (int i = 0; i < N - 1; ++i) {
		int u, v; ll w; cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	vector<int> dep(N + 1); vector<ll> dist(N + 1);
	int h = (int)ceil(log2(N)); ++h;
	vector<vector<int>> f(h, vector<int>(N + 1));
	init(N, adj, dep, dist, h, f);
	int M; cin >> M;
	while (M--) {
		int type; cin >> type;
		if (type == 1) {
			int u, v; cin >> u >> v;
			cout << distance(u, v, dep, dist, h, f) << '\n';
		} else {
			int u, v, k; cin >> u >> v >> k;
			cout << query(u, v, k, dep, h, f) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}