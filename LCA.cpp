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

int lca(int u, int v, vector<int>& dep, vector<vector<int>>& f) {
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

void init(vector<vector<pair<int, ll>>>& adj, vector<int>& dep, vector<ll>& dist, vector<vector<int>>& f) {
	const int h = f.size(), MAX_V = adj.size();
	// root: 1
    dfs(1, -1, 0ll, f, dep, dist, adj);
	for (int i = 1; i < h; ++i) {
		for (int j = 0; j < MAX_V; ++j) {
			if (f[i - 1][j] == -1) f[i][j] = -1;
			else f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
}

ll distance(int u, int v, vector<int>& dep, vector<ll>& dist, int& h, vector<vector<int>>& f) {
	int l = lca(u, v, dep, f);
	return dist[u] + dist[v] - dist[l] * 2;
}

void solve() {
	int MAX_V;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<int> dep(MAX_V); vector<ll> dist(MAX_V);
	int h = (int)ceil(log2(MAX_V)); ++h;
	vector<vector<int>> f(h, vector<int>(MAX_V));
	init(adj, dep, dist, f);
}