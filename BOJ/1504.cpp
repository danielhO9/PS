#include <bits/stdc++.h>
using namespace std;

int N, E, v1, v2, dis[801], v1v2;
long long ans[2];
vector<pair<int, int>> graph[801];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;

void dijkstra(int t) {
	int v = t == 1 ? v1 : t == 0 ? 1 : v2;
	for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
	dis[v] = 0; Q.push({0, v});
	int a, c;
	while (!Q.empty()) {
		a = Q.top().second; c = Q.top().first;
		Q.pop();
		if (dis[a] < c) continue;
		else {
			for (auto i: graph[a]) if (dis[i.second] > i.first + c) {
				dis[i.second] = i.first + c;
				Q.push({i.first + c, i.second});
			}
		}
	}
	if (t == 1) ans[0] += dis[N];
	if (t == 2) {
		ans[1] += dis[N];
		v1v2 = dis[v1];
	}
	if (t == 0) {
		ans[0] += dis[v2];
		ans[1] += dis[v1];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> E;
	int a, b, c;
	for (int i = 0; i < E; ++i) {
		cin >> a >> b >> c;
		graph[a].push_back({c, b});
		graph[b].push_back({c, a});
	}
	cin >> v1 >> v2;
	for (int i = 0; i < 3; ++i) dijkstra(i);
	if (v1v2 >= INT32_MAX || ans[0] >= INT32_MAX || ans[1] >= INT32_MAX) cout << -1;
	else cout << min(ans[0], ans[1]) + v1v2;
}