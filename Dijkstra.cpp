#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// MAX_V: max vertex number
// time complexity: (V+E)logV
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

void solve() {
	int MAX_V;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<ll> ans = dijkstra(1, adj);
}