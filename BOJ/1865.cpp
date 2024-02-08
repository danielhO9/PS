#include <bits/stdc++.h>
using namespace std;

struct way {
	int start, stop, distance;
};

int N, M, W, dis[501], visited[501];
vector<way> graph;

bool hasCycle(int x) {
	for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
	dis[x] = 0; visited[x] = 1;
	for (int i = 0; i < N; ++i) for (auto j: graph) {
		if (dis[j.start] != INT32_MAX && dis[j.start] + j.distance < dis[j.stop]) {
			dis[j.stop] = dis[j.start] + j.distance;
			visited[j.stop] = 1;
			if (i == N - 1) return true;
		}
	}
	return false;
}

void solution() {
	cin >> N >> M >> W;
	int a, b, d;
	graph.clear();
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> d;
		graph.push_back({a, b, d});
		graph.push_back({b, a, d});
	}
	for (int i = 0; i < W; ++i) {
		cin >> a >> b >> d;
		graph.push_back({a, b, -d});
	}
	for (int i = 1; i <= N; ++i) {
		if (!visited[i] && hasCycle(i)) {
			cout << "YES" << "\n";
			return;
		}
	}
	cout << "NO" << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int TC; cin >> TC;
	for (int i = 0; i < TC; ++i) solution();
}