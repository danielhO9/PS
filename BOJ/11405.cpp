#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = INT32_MAX;
const int MAX_V = 202;

pair<LL, LL> networkFlow(int MAX_V, vector<vector<LL>>& capacity, vector<vector<LL>>& flow, vector<vector<LL>>& cost, vector<vector<int>>& adj, int source, int sink) {
	for (int i = 0; i < MAX_V; ++i) for (int j = 0; j < MAX_V; ++j) flow[i][j] = 0;
	LL totalFlow = 0;
	LL totalCost = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		vector<LL> dis(MAX_V, INF);
		vector<bool> inQ(MAX_V, false);
		queue<int> q;
		dis[source] = 0; inQ[source] = true; q.push(source);
		parent[source] = source;
		while (!q.empty()) {
			int here = q.front(); q.pop(); inQ[here] = false;
			for (auto there: adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0 && dis[there] > dis[here] + cost[here][there]) {
					dis[there] = dis[here] + cost[here][there];
					parent[there] = here;
					if (!inQ[there]) {
						q.push(there);
						inQ[there] = true;
					}
				}
			}
		}
		if (parent[sink] == -1) break;
		LL amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
			totalCost += amount * cost[parent[p]][p];
			// cout << p << ' ';
		}
		totalFlow += amount;
		// cout << totalCost << '\n';
	}
	return make_pair(totalFlow, totalCost);
}

void solve() {
	int n, m;
	// source: 0, 도서관: 1 ~ m, 사람: 101 ~ 100 + n, sink: 201
	vector<vector<LL>> capacity(MAX_V, vector<LL>(MAX_V)), flow(MAX_V, vector<LL>(MAX_V)), cost(MAX_V, vector<LL>(MAX_V));
	vector<vector<int>> adj(MAX_V, vector<int>(MAX_V));
	cin >> n >> m;
	for (int i = 101; i <= 100 + n; ++i) {
		cin >> capacity[i][201];
		adj[i].push_back(201);
		adj[201].push_back(i);
	}
	for (int i = 1; i <= m; ++i) {
		cin >> capacity[0][i];
		adj[0].push_back(i);
		adj[i].push_back(0);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 101; j <= 100 + n; ++j) {
			capacity[i][j] = 987654321;
			adj[i].push_back(j);
			adj[j].push_back(i);
			cin >> cost[i][j];
			cost[j][i] = -cost[i][j];
		}
	}
	auto ans = networkFlow(MAX_V, capacity, flow, cost, adj, 0, 201);
	cout << ans.second;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}