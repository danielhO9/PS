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
	int N, M, K; cin >> N >> M >> K; ++K;
	int a, b; LL d;
	vector<vector<pair<int, LL>>> adj((N + 1) * K + 1);
	while (M--) {
		cin >> a >> b >> d;
		for (int i = 0; i < K; ++i) {
			adj[a * K + i].push_back({b * K + i, d});
			adj[b * K + i].push_back({a * K + i, d});
			if (i != 0) {
				adj[a * K + i].push_back({b * K + i - 1, 0});
				adj[b * K + i].push_back({a * K + i - 1, 0});
			}
		}
	}
	for (int i = 0; i < K; ++i) {
		adj[0].push_back({1 * K + i, 0});
		adj[N * K + i].push_back({N * K + K, 0});
	}
	vector<LL> ans = dijkstra(0, adj, (N + 1) * K + 1);
	cout << ans[N * K + K];
}