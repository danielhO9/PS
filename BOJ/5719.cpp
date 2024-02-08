#include <bits/stdc++.h>
using namespace std;

int N, M;
int S, D;
vector<int> parent[500];
vector<pair<int, int>> graph[500];
int dis[500];
bool visited[500][500];

void dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
	for (int i = 0; i < N; ++i) dis[i] = INT32_MAX;
	dis[S] = 0; Q.push({0, S});
	while (!Q.empty()) {
		pair<int, int> here = Q.top(); Q.pop();
		if (dis[here.second] < here.first) continue;
		else {
			for (auto there: graph[here.second]) {
				if (!visited[here.second][there.first] && dis[there.first] > there.second + here.first) {
					parent[there.first].clear();
					parent[there.first].push_back(here.second);
					dis[there.first] = there.second + here.first;
					Q.push({dis[there.first], there.first});
				} else if (dis[there.first] == there.second + here.first) {
					parent[there.first].push_back(here.second);
				}
			}
		}
	}
}

void solve() {
	cin >> S >> D; int U, V; int P;
	for (int i = 0; i < N; ++i) {
		graph[i].clear();
		parent[i].clear();
	}
	for (int i = 0; i < M; ++i) {
		cin >> U >> V >> P;
		graph[U].push_back({V, P});
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) visited[i][j] = false;
	dijkstra();
	if (dis[D] == INT32_MAX) {
		cout << -1 << '\n';
		return;
	}
	int v = D;
	deque<int> DQ; DQ.push_back(v);
	while (!DQ.empty()) {
		int temp = DQ.front(); DQ.pop_front();
		for (auto i: parent[temp]) if (!visited[i][temp]) {
			visited[i][temp] = true;
			DQ.push_back(i);
		}
	}
	dijkstra();
	if (dis[D] == INT32_MAX) {
		cout << -1 << '\n';
		return;
	}
	cout << dis[D] << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (cin >> N >> M) {
		if (N == 0 && M == 0) break;
		solve();
	}
}