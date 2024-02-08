#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 2003;
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
	int n, m, k;
	// source: 0, 임시: 2001, 직원: 1 ~ n, 일: 1001 ~ 1001 + m, sink: 2002
	cin >> n >> m >> k;
	V = n + m + 3;
	for (int i = 1; i <= n; ++i) {
		capacity[0][i] = 1;
		adj[0].push_back(i);
		adj[i].push_back(0);
	}
	adj[0].push_back(n + m + 1);
	adj[n + m + 1].push_back(0);
	capacity[0][n + m + 1] = k;
	for (int i = 1; i <= n; ++i) {
		capacity[n + m + 1][i] = 1;
		adj[n + m + 1].push_back(i);
		adj[i].push_back(n + m + 1);
	}
	for (int i = 1; i <= n; ++i) {
		int cnt; cin >> cnt;
		while (cnt--) {
			int w; cin >> w;
			w += n;
			capacity[i][w] = 1;
			adj[i].push_back(w);
			adj[w].push_back(i);
		}
	}
	for (int i = n + 1; i <= n + m; ++i) {
		capacity[i][n + m + 2] = 1;
		adj[n + m + 2].push_back(i);
		adj[i].push_back(n + m + 2);
	}
	auto ans = networkFlow(0, n + m + 2);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}