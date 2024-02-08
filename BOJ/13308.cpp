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

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	vector<vector<pair<int, LL>>> adj(N + 1);
	LL cost[N + 1]; for (int i = 1; i <= N; ++i) cin >> cost[i];
	while (M--) {
		int a, b; LL d; cin >> a >> b >> d;
		adj[a].push_back({b, d});
		adj[b].push_back({a, d});	
	}
	vector<vector<pair<int, LL>>> graph(N + 1);
	for (int i = 1; i <= N; ++i) {
		vector<LL> dist = dijkstra(i, adj, N + 1);
		LL d;
		for (int j = 1; j <= N; ++j) {
			if (dist[j] == LLONG_MAX) d = LLONG_MAX;
			else d = dist[j] * cost[i];
			graph[i].push_back({j, d});
		}
	}
	vector<LL> ans = dijkstra(1, graph, N + 1);
	cout << ans[N];
}