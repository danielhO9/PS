#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 801;

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
	int n, p;
	// source: 0, 임시: 2001, 직원: 1 ~ n, 일: 1001 ~ 1001 + m, sink: 2002
	cin >> n >> p;
	for (int i = 3; i <= n; ++i) {
		adj[i].push_back(i + n);
		adj[i + n].push_back(i);
		capacity[i][i + n] = 1;
	}
	for (int i = 0; i < p; ++i) {
		int u, v; cin >> u >> v;
		if (u != 1 && u != 2) u += n;
		adj[u].push_back(v);
		capacity[u][v] = 1;
		adj[v].push_back(u);
		if (u != 1 && u != 2) u -= n;
		if (v != 1 && v != 2) v += n;
		adj[u].push_back(v);
		adj[v].push_back(u);
		capacity[v][u] = 1;
	}
	auto ans = networkFlow(1, 2);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}