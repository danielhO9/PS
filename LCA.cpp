#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
vector<pair<int, ll>> adj[MAX_V];
int dep[MAX_V];
ll dis[MAX_V];
vector<vector<int>> f;

void dfs(int v, int p, ll d) {
    f[0][v] = p;
    if (p == -1) {
        dep[v] = 0; dis[v] = 0ll;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [u, nd]: adj[v]) if (u != p) dfs(u, v, nd);
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

void init(int v = MAX_V) {
	const int h = f.size();
	// root: 1
    dfs(1, -1, 0ll);
	for (int i = 1; i < h; ++i) {
		for (int j = 0; j < v; ++j) {
			if (f[i - 1][j] == -1) f[i][j] = -1;
			else f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
}

ll getDis(int u, int v) {
	int l = lca(u, v);
	return dis[u] + dis[v] - dis[l] * 2;
}

void solve() {
	
	int h = (int)ceil(log2(MAX_V)); ++h;
	f = vector<vector<int>>(h, vector<int>(MAX_V));
	init(MAX_V);
}