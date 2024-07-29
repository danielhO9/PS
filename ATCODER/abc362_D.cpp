#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dijkstra(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX);
	dist[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	int N, M; cin >> N >> M;
	int MAX_V = N * 2 + 1;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	for (int i = 1; i <= N; ++i) {
		ll tmp; cin >> tmp;
		adj[i].push_back({i + N, tmp});
		adj[i + N].push_back({i, tmp});
	}
	for (int i = 0; i < M; ++i) {
		int u, v; ll w; cin >> u >> v >> w;
		adj[u + N].push_back({v, w});
		adj[v + N].push_back({u, w});
	}
	vector<ll> ans = dijkstra(1, adj);
	for (int i = 2; i <= N; ++i) cout << ans[i + N] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}