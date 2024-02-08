#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = INT32_MAX;

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

void solve(int v, int e) {
	// source: 0, 중간지점: 1 ~ 2 * v, sink: 2 * v + 1
	const int MAX_V = 2 * v + 2;
	vector<vector<LL>> capacity(MAX_V, vector<LL>(MAX_V)), flow(MAX_V, vector<LL>(MAX_V)), cost(MAX_V, vector<LL>(MAX_V));
	vector<vector<int>> adj(MAX_V, vector<int>(MAX_V));
	capacity[0][1] = 2;
	adj[0].push_back(1);
	adj[1].push_back(0);
	for (int i = 2; i < v; ++i) {
		capacity[i][i + v] = 1;
		adj[i].push_back(i + v);
		adj[i + v].push_back(i);
	}
	for (int i = 0; i < e; ++i) {
		int a, b; LL c; cin >> a >> b >> c;
		if (a != 1) a += v;
		capacity[a][b] = 1;
		adj[a].push_back(b);
		adj[b].push_back(a);
		cost[a][b] = c;
		cost[b][a] = -c;
	}
	capacity[v][2 * v + 1] = 2;
	adj[v].push_back(2 * v + 1);
	adj[2 * v + 1].push_back(v);
	auto ans = networkFlow(MAX_V, capacity, flow, cost, adj, 0, 2 * v + 1);
	cout << ans.second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int v, e;
	while (cin >> v >> e) solve(v, e);
}