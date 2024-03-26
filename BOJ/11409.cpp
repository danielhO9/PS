#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 987654321;

pair<ll, ll> networkFlow(int source, int sink, vector<vector<int>>& adj, vector<vector<ll>>& capacity, vector<vector<ll>>& flow, vector<vector<ll>>& cost) {
	const int MAX_V = adj.size();
	for (int i = 0; i < MAX_V; ++i) for (int j = 0; j < MAX_V; ++j) flow[i][j] = 0;
	ll totalFlow = 0;
	ll totalCost = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		vector<ll> dis(MAX_V, INF);
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
		ll amount = INF;
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

void addEdge(int s, int e, ll cap, ll dis, vector<vector<int>>& adj, vector<vector<ll>>& capacity, vector<vector<ll>>& cost) {
	adj[s].push_back(e);
	adj[e].push_back(s);
	capacity[s][e] = cap;
	cost[s][e] = dis;
	cost[e][s] = -dis;
}

void solve() {
	// 일: 1 - m, 직원: m + 1 - m + n, source: 0, sink: m + n + 1
	int N, M; cin >> N >> M;
	int MAX_V = N + M + 2;
	int source = 0, sink = N + M + 1;
	vector<vector<int>> adj(MAX_V, vector<int>(MAX_V));
	vector<vector<ll>> capacity(MAX_V, vector<ll>(MAX_V)), flow(MAX_V, vector<ll>(MAX_V)), cost(MAX_V, vector<ll>(MAX_V));
	for (int i = M + 1; i <= M + N; ++i) addEdge(0, i, 1, 0, adj, capacity, cost);
	for (int i = M + 1; i <= M + N; ++i) {
		int t; cin >> t;
		while (t--) {
			int num; cin >> num;
			int dis; cin >> dis;
			addEdge(i, num, 1, 10000 - dis, adj, capacity, cost);
		}
	}
	for (int i = 1; i <= M; ++i) addEdge(i, M + N + 1, 1, 0, adj, capacity, cost);
	auto ans = networkFlow(source, sink, adj, capacity, flow, cost);
	cout << ans.first << '\n' << ans.first * 10000 - ans.second;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}