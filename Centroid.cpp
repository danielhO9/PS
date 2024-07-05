#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Vertex {
	int e; ll w;
};

vector<vector<Vertex>> adj;
vector<int> sz;
vector<bool> vis;

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: adj[v]) if (i.e != p && !vis[i.e]) sz[v] += getSize(i.e, v);
    return sz[v];
}

int getCent(int v, int p, int& sub){
    for(auto i: adj[v]) if (i.e != p && !vis[i.e] && sz[i.e] * 2 > sub) return getCent(i.e, v, sub);
    return v;
}

int centroid(int v, int p) {
    getSize(v, p); int sub = sz[v]; 
	return getCent(v, p, sub);
}

ll dnc(int v) {
    getSize(v, -1); int csz = sz[v];
	int cent = getCent(v, -1, csz); vis[cent] = true;

	ll ret = 0;
	// compute

    for (auto i: adj[cent]) if (!vis[i.e]) ret += dnc(i.e);
	return ret;
}

void solve() {
	int MAX_N;
	adj.resize(MAX_N);
	sz.resize(MAX_N);
	vis = vector<bool>(MAX_N, false);

	int src = 1;
	dnc(src);
}