#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 987654321;

struct Edge {
	int vertex;
	ll capacity;
	ll cost;
	int reverse;
	ll flow = 0;
};

const int MAX_V = 502;
vector<Edge> adj[MAX_V];

void spfa(vector<int>& parent, vector<int>& ind, vector<bool>& inQ, vector<ll>& dis, int source) {
	for (auto& i: parent) i = -1;
	for (int i = 0; i < inQ.size(); ++i) inQ[i] = false;
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
}

// time complexity: (V+E)*F
// V: maximum vertex + 1
pair<ll, ll> networkFlow(int source, int sink, const int V) {
	for (int i = 0; i < V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	ll totalCost = 0;
	vector<int> parent(V), ind(V);
	vector<bool> inQ(V); vector<ll> dis(V);
	while (true) {
		spfa(parent, ind, inQ, dis, source);
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

void addEdge(int s, int e, ll cap, ll dis) {
	adj[s].push_back({e, cap, dis, (int)adj[e].size()});
	adj[e].push_back({s, 0, -dis, (int)adj[s].size() - 1});
}

void solve() {
	int n, m; cin >> n >> m;
	for (int i = 0; i < n + 2; ++i) adj[i].clear();
	int source = 0, sink = n + 1;
	while (m--) {
		int x, y; cin >> x >> y;
		addEdge(x, y, INF, 1);
		addEdge(y, x, INF, 1);
	}
	for (int i = 1; i <= n; ++i) {
		int col; cin >> col;
		if (col == 0) addEdge(i, sink, 1, 0);
	}
	for (int i = 1; i <= n; ++i) {
		int col; cin >> col;
		if (col == 0) addEdge(source, i, 1, 0);
	}
	auto ans = networkFlow(source, sink, n + 2);
	cout << ans.second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}