#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 802;
int n, m;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V], cost[MAX_V][MAX_V];
vector<int> adj[MAX_V];

pair<int, int> networkFlow(int source, int sink) {
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	int totalCost = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		vector<int> dis(MAX_V, INF);
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
		int amount = INF;
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


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	// 일: 1 - m, 직원: m + 1 - m + n, source: 0, sink: m + n + 1
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
	auto ans = networkFlow(0, m + n + 1);
	cout << ans.first << '\n' << ans.second;
}