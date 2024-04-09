#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll K;
vector<int> dis(1000001, 987654321);

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

void getDis(int v, int p, vector<vector<Vertex>>& adj, int dep, int w, vector<pair<int, ll>>& ndis) {
	for (auto i: adj[v]) if (i.e != p && !vis[i.e] && w + i.w <= K) {
		ndis.push_back({dep + 1, i.w + w});
		getDis(i.e, v, adj, dep + 1, w + i.w, ndis);
	}
}

int dnc(int v, vector<vector<Vertex>>& adj) {
	int ret = adj.size();
	int cent = centroid(adj, v, -1);
	vis[cent] = true;
	vector<int> changed;
	for (auto i: adj[cent]) if (!vis[i.e]) {

		vector<pair<int, ll>> ndis;
		if (i.w <= K) {
			ndis.push_back({1, i.w});
			getDis(i.e, cent, adj, 1, i.w, ndis);
		}

		for (auto [dep, w]: ndis) ret = min(ret, dis[K - w] + dep);
		for (auto [dep, w]: ndis) if (dis[w] > dep) {
			dis[w] = dep;
			changed.push_back(w);
		}
	}
	for (auto i: changed) dis[i] = 987654321;
	for (auto i: adj[cent]) if (!vis[i.e]) ret = min(ret, dnc(i.e, adj));
	return ret;
}

void solve() {
	int N; cin >> N >> K;
	int MAX_N = N;
	vector<vector<Vertex>> adj(MAX_N);
	for (int i = 0; i < N - 1; ++i) {
		int s, e; ll w; cin >> s >> e >> w;
		adj[s].push_back({e, w});
		adj[e].push_back({s, w});
	}
	sz.resize(MAX_N); vis = vector<bool>(MAX_N, false);
	dis[0] = 0;
	int ans = dnc(0, adj);
	if (ans == N) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}