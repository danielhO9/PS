#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Edge {
	LL cost; int here, degree;
	bool operator < (const Edge& o) const { return cost < o.cost; }
};

vector<vector<LL>> dijkstra(int src, vector<vector<pair<int, LL>>>& adj, int V) {
	vector<vector<LL>> dist(V + 1, vector<LL>(V, LLONG_MAX));
	priority_queue<Edge> pq;
	pq.push(Edge{0, src, 0});
	while(!pq.empty()) {
		LL cost = -pq.top().cost;
		int here = pq.top().here;
		int degree = pq.top().degree;
		pq.pop();
		if (dist[here][degree] < cost) continue;
		if (degree == V - 1) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			LL nextDist = cost + adj[here][i].second;
			if (dist[there][degree + 1] > nextDist) {
				dist[there][degree + 1] = nextDist;
				pq.push(Edge{-nextDist, there, degree + 1});
			}
		}
	}
	return dist;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int N, M, K; cin >> N >> M >> K;
	vector<vector<pair<int, LL>>> graph(N + 1);
	int S, D; cin >> S >> D;
	int a, b; LL w;
	while (M--) {
		cin >> a >> b >> w;
		graph[a].push_back({b, w});
		graph[b].push_back({a, w});
	}
	LL k[K + 1]; for (int i = 1; i <= K; ++i) cin >> k[i];
	k[0] = 0;
	vector<vector<LL>> ans = dijkstra(S, graph, N);
	for (int i = 0; i <= K; ++i) {
		for (LL j = 0; j < N; ++j) if (ans[D][j] != LLONG_MAX) ans[D][j] += k[i] * j;
		cout << *min_element(next(ans[D].begin()), ans[D].end()) << '\n';
	}
}