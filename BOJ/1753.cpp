#include <bits/stdc++.h>
using namespace std;

int V, E, K, dis[20001];
vector<pair<int, int>> graph[20001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> V >> E >> K;
	int u, v, w;
	for (int i = 0; i < E; ++i) {
		cin >> u >> v >> w;
		graph[u].push_back({w, v});
	}
	for (int i = 1; i <= V; ++i) dis[i] = INT32_MAX;
	dis[K] = 0; Q.push({0, K});
	while (!Q.empty()) {
		w = Q.top().first; v = Q.top().second;
		Q.pop();
		if (dis[v] < w) continue;
		else {
			for (auto i: graph[v]) if (dis[i.second] > i.first + w) {
				dis[i.second] = i.first + w;
				Q.push({i.first + w, i.second});
			}
		}
	}
	for (int i = 1; i <= V; ++i) {
		if (dis[i] == INT32_MAX) cout << "INF" << "\n";
		else cout << dis[i] << "\n";
	}
}