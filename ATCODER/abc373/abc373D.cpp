#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x[200001];

void dijkstra(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	x[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (x[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (x[there] > nextDist) {
				x[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
}

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	int N, M; cin >> N >> M;
	int MAX_V = N + 1;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	for (int i = 0; i < M; ++i) {
		ll u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, -w});
	}
	for (int i = 1; i <= N; ++i) {
		x[i] = LLONG_MAX;
	}
	for (int i = 1; i <= N; ++i) {
		if (x[i] != LLONG_MAX) continue;
		dijkstra(i, adj);
	}
	for (int i = 1; i <= N; ++i) cout << x[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}