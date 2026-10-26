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
		}
		totalFlow += amount;
	}
	return make_pair(totalFlow, totalCost);
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	// 행: 2 - 1+n, 열: 2+n - 1+m+n, source: 0, sink: 1
	cin >> n >> m; int temp, temp1 = 0, temp2 = 0, temp3 = 0;
	for (int i = 2; i <= n + 1; ++i) for (int j = n + 2; j <= m + n + 1; ++j) {
		cin >> temp;
		capacity[i][j] = 1;
		adj[i].push_back(j);
		adj[j].push_back(i);
		cost[i][j] = 1 - temp;
		cost[j][i] = temp - 1;
		temp3 += temp;
	}
	for (int i = 2; i <= n + 1; ++i) {
		cin >> capacity[0][i];
		temp1 += capacity[0][i];
		adj[i].push_back(0);
		adj[0].push_back(i);
	}
	for (int i = n + 2; i <= m + n + 1; ++i) {
		cin >> capacity[i][1];
		temp2 += capacity[i][1];
		adj[i].push_back(1);
		adj[1].push_back(i);
	}
	auto ans = networkFlow(0, 1);
	if (ans.first != temp1 || ans.first != temp2) cout << -1;
	else cout << temp3 - ans.first + ans.second * 2;
}