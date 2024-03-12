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

void solve() {
	// max vertex number
	int V;
	vector<vector<pair<int, ll>>> adj(V + 1);
	vector<int> dep(V + 1); vector<ll> dist(V + 1);
	int h = (int)ceil(log2(V)); ++h;
	vector<vector<int>> f(h, vector<int>(V + 1));
	init(V, adj, dep, dist, h, f);
}