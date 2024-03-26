#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 987654321;
const ll table[5][5] = {
	{10, 8, 7, 5, 1},
	{8, 6, 4, 3, 1},
	{7, 4, 3, 2, 1},
	{5, 3, 2, 2, 1},
	{1, 1, 1, 1, 0}
};
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

struct Edge {
	int vertex;
	ll capacity;
	ll cost;
	int reverse;
	ll flow = 0;
};

pair<ll, ll> networkFlow(int source, int sink, vector<vector<Edge>>& adj) {
	const int MAX_V = adj.size();
	for (int i = 0; i < MAX_V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	ll totalCost = 0;
	int parent[MAX_V], ind[MAX_V];
	ll dis[MAX_V];
	bool inQ[MAX_V];
	while (true) {
		memset(parent, -1, sizeof(parent));
		memset(inQ, 0, sizeof(inQ));
		for (auto& i: dis) i = INF;
		queue<int> q;
		dis[source] = 0; inQ[source] = true; q.push(source);
		parent[source] = source;
		while (!q.empty()) {
			int here = q.front(); q.pop(); inQ[here] = false;
			for (int i = 0; i < adj[here].size(); ++i) {
				Edge& edge = adj[here][i];
				int there = edge.vertex;
				if (edge.capacity - edge.flow > 0 && dis[there] > dis[here] + edge.cost) {
					dis[there] = dis[here] + edge.cost;
					parent[there] = here;
					ind[there] = i;
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
			Edge& edge = adj[parent[p]][ind[p]];
			amount = min(edge.capacity - edge.flow, amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			Edge& edge = adj[parent[p]][ind[p]];
			edge.flow += amount;
			adj[edge.vertex][edge.reverse].flow -= amount;
			totalCost += amount * edge.cost;
		}
		totalFlow += amount;
	}
	return make_pair(totalFlow, totalCost);
}

void addEdge(int s, int e, ll cap, ll dis, vector<vector<Edge>>& adj) {
	adj[s].push_back({e, cap, dis, (int)adj[e].size()});
	adj[e].push_back({s, 0, -dis, (int)adj[s].size() - 1});
}

void solve() {
	int N, M; cin >> N >> M;
	int tofu[N][M];
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		char c; cin >> c;
		tofu[i][j] = min(c - 'A', 4);
	}
	int MAX_V = N * M + 2;
	int source = N * M, sink = N * M + 1;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		int num = i * M + j;
		if ((i + j) % 2 == 0) {
			addEdge(source, num, 1, 0, adj);
			for (int k = 0; k < 4; ++k) {
				int ny = i + dy[k], nx = j + dx[k];
				if (0 <= ny && ny < N && 0 <= nx && nx < M) {
					int nnum = ny * M + nx;
					addEdge(num, nnum, 1, -table[tofu[i][j]][tofu[ny][nx]], adj);
				}
			}
			addEdge(num, sink, 1, 0, adj);
		} else {
			addEdge(num, sink, 1, 0, adj);
		}
	}
	auto ans = networkFlow(source, sink, adj);
	cout << -ans.second;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}