#include <bits/stdc++.h>
using namespace std;

int N, M, X, dis1[1001], dis2[1001], ans;
vector<pair<int, int>> graph1[1001], graph2[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;

void dijkstra(vector<pair<int, int>>* graph, int* dis) {
	for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
	Q.push({0, X}); dis[X] = 0;
	int tv, tt;
	while (!Q.empty()) {
		tv = Q.top().second; tt = Q.top().first;
		Q.pop();
		if (dis[tv] < tt) continue;
		for (auto i: graph[tv]) if (dis[i.second] > tt + i.first) {
			dis[i.second] = tt + i.first;
			Q.push({tt + i.first, i.second});
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> X;
	int a, b, t;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> t;
		graph1[a].push_back({t, b});
		graph2[b].push_back({t, a});
	}
	dijkstra(graph1, dis1); dijkstra(graph2, dis2);
	for (int i = 1; i <= N; ++i) ans = max(ans, dis1[i] + dis2[i]);
	cout << ans;
}