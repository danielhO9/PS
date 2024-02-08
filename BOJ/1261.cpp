#include <bits/stdc++.h>
using namespace std;
int INF = 987654321;

vector<int> dijkstra(int src, vector<vector<pair<int, int>>>& adj, int V) {
	vector<int> dist(V, INF);
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
	int N, M; cin >> N >> M;
	bool wall[M * N];
	for (int i = 0; i < M; ++i) {
		string s; cin >> s;
		for (int j = 0; j < N; ++j) wall[N * i + j] = s[j] - '0';
	}
	vector<vector<pair<int, int>>> adj(N * M);
	for (int i = 0; i < M; ++i) for (int j = 0; j < N; ++j) {
		if (i != 0) adj[N * i + j].push_back({N * i + j - N, wall[N * i + j - N]});
		if (j != 0) adj[N * i + j].push_back({N * i + j - 1, wall[N * i + j - 1]});
		if (i != M - 1) adj[N * i + j].push_back({N * i + j + N, wall[N * i + j + N]});
		if (j != N - 1) adj[N * i + j].push_back({N * i + j + 1, wall[N * i + j + 1]});
	}
	vector<int> ans = dijkstra(0, adj, N * M);
	cout << ans[N * M - 1];
}