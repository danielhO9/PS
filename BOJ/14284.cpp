#include <bits/stdc++.h>
using namespace std;

int n, m;

/**
 * Description: Dijkstra's Algorithm for finding the shortest paths from a source vertex to aint other vertices.
 *  Assumes non-negative edge weights.
 * Time: $O((V + E) \log V)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_V = 5001;
vector<pair<int, int>> adj[MAX_V];

// time complexity: (V+E)logV
// V: maximum vertex + 1
vector<int> dijkstra(int src, int V) {
	vector<int> dist(V, INT32_MAX);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
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
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }
    int s, e; cin >> s >> e;
    auto dis = dijkstra(s, n + 1);
    cout << dis[e];
}