#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 302;
int V;

vector<int> adj[MAX_V];
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int networkFlow(int source, int sink) {
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (auto there: adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

void solve() {
	int n, k, d;
	// source: 0, 사람: 200, 음식: 201 ~ 300, sink: 301
	cin >> n >> k >> d;
	for (int i = 1; i <= n; ++i) {
		capacity[0][i] = k;
		adj[0].push_back(i);
		adj[i].push_back(0);
	}
	for (int i = 201; i <= 200 + d; ++i) {
		cin >> capacity[i][301];
		adj[i].push_back(301);
		adj[301].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		int c; cin >> c;
		while (c--) {
			int j; cin >> j;
			j += 200;
			capacity[i][j] = 1;
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
	}
	auto ans = networkFlow(0, 301);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}