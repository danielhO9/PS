#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

vector<LL> dijkstra(int src, vector<vector<pair<int, LL>>>& adj, int V) {
	vector<LL> dist(V, LLONG_MAX);
	dist[src] = 0;
	priority_queue<pair<LL, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		LL cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			LL nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}