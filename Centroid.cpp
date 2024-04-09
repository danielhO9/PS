#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Vertex {
	int e; ll w;
};

vector<int> sz;
vector<bool> vis;

int getSize(vector<vector<Vertex>>& adj, int v, int p){
    sz[v] = 1;
    for(auto i: adj[v]) if (i.e != p && !vis[i.e]) sz[v] += getSize(adj, i.e, v);
    return sz[v];
}

int getCent(vector<vector<Vertex>>& adj, int v, int p, int& sub){
    for(auto i: adj[v]) if (i.e != p && !vis[i.e] && sz[i.e] * 2 > sub) return getCent(adj, i.e, v, sub);
    return v;
}

int centroid(vector<vector<Vertex>>& adj, int v, int p) {
    getSize(adj, v, p); int sub = sz[v]; 
	return getCent(adj, v, p, sub);
}

void solve() {
	int MAX_N;
	vector<vector<Vertex>> adj(MAX_N);
	sz.resize(MAX_N); vis = vector<bool>(MAX_N, false);
	centroid(adj, 0, -1);
}