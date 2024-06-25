#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e16;

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
		ll amount = LLONG_MAX;
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

// time complexity: (V+E)*F
void solve() {
	int N, P; cin >> N >> P;
	ll A[N + 1][N + 1], C[N + 1][N + 1], O[N + 1][N + 1];
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) cin >> C[i][j];
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) cin >> A[i][j];
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) cin >> O[i][j];
	int MAX_V = N + 1;
	int source = 0, sink = N;
	vector<vector<Edge>> adj(MAX_V);
	addEdge(source, 1, P, 0, adj);
	for (int i = 1; i < N; ++i) addEdge(i, i + 1, 987654321, 0ll, adj);
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) addEdge(i, j, A[i][j], -C[i][j], adj);
	ll rem = 0;
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
		addEdge(i, j, O[i][j], -1e8, adj);
		rem += 1e8 * O[i][j];
	}
	auto ans = networkFlow(source, sink, adj);
	cout << -ans.second - rem << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}