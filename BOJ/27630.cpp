#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	int s, e;
	ll P, T;
};

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
	set<int> s[N + 1];
	unordered_map<int, int> m[N + 1];
	vector<Edge> edges;

	s[1].insert(1);
	s[N].insert(1);
	for (int i = 0; i < M; ++i) {
		int a, b; ll P, T; cin >> a >> b >> P >> T;
		edges.push_back({a, b, P, T});
		s[a].insert(P);
		s[b].insert(P);
	}

	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		auto itr = s[i].begin();
		assert(itr != s[i].end());
		while (itr != s[i].end()) {
			m[i][*itr] = ++cnt;
			++itr;
		}
	}

	int MAX_V = cnt + 1;
	vector<vector<pair<int, ll>>> adj(MAX_V);

	for (int i = 1; i <= N; ++i) {
		auto itr = s[i].begin();
		while (next(itr) != s[i].end()) {
			auto nxt = next(itr);
			adj[m[i][*nxt]].push_back({m[i][*itr], (*nxt) - (*itr)});
			adj[m[i][*itr]].push_back({m[i][*nxt], (*nxt) - (*itr)});
			++itr;
		}
	}

	for (auto e: edges) {
		adj[m[e.s][e.P]].push_back({m[e.e][e.P], e.T});
		adj[m[e.e][e.P]].push_back({m[e.s][e.P], e.T});
	}
	vector<ll> ans = dijkstra(1, adj);
	cout << ans[m[N][1]];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}