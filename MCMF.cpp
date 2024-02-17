#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = INT32_MAX;
const int MAX_V = 802;

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
	// 일: 1 - m, 직원: m + 1 - m + n, source: 0, sink: m + n + 1
	vector<vector<LL>> capacity(MAX_V, vector<LL>(MAX_V)), flow(MAX_V, vector<LL>(MAX_V)), cost(MAX_V, vector<LL>(MAX_V));
	vector<vector<int>> adj(MAX_V, vector<int>(MAX_V));
	cin >> n >> m;
	for (int i = m + 1; i <= m + n; ++i) {
		capacity[0][i] = 1;
		adj[0].push_back(i);
		adj[i].push_back(0);
	}
	for (int i = m + 1; i <= m + n; ++i) {
		int t; cin >> t;
		for (int j = 1; j <= t; ++j) {
			int num;
			cin >> num;
			cin >> cost[i][num];
			cost[num][i]= -cost[i][num];
			capacity[i][num] = 1;
			adj[i].push_back(num);
			adj[num].push_back(i);
		}
	}
	for (int i = 1; i <= m; ++i) {
		capacity[i][m + n + 1] = 1;
		adj[i].push_back(m + n + 1);
		adj[m + n + 1].push_back(i);
	}
	auto ans = networkFlow(MAX_V, capacity, flow, cost, adj, 0, m + n + 1);
	cout << ans.first << '\n' << ans.second;
}