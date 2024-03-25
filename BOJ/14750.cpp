#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }

ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

bool isMeet(const pair<ll, ll>& a1, const pair<ll, ll>& a2, const pair<ll, ll>& b1, const pair<ll, ll>& b2) {
	ll ab1 = ccw(a1, a2, b1); if (ab1 != 0) ab1 /= abs(ab1);
	ll ab2 = ccw(a1, a2, b2); if (ab2 != 0) ab2 /= abs(ab2);
	ll ba1 = ccw(b1, b2, a1); if (ba1 != 0) ba1 /= abs(ba1);
	ll ba2 = ccw(b1, b2, a2); if (ba2 != 0) ba2 /= abs(ba2);
	if (ab1 * ab2 == 0 && ba1 * ba2 == 0) return min(b1, b2) <= max(a1, a2) && min(a1, a2) <= max(b1, b2);
	return ab1 * ab2 <= 0 && ba1 * ba2 <= 0;
}

bool isMeet(const pair<ll, ll>& a, const pair<ll, ll>& b1, const pair<ll, ll>& b2) {
	ll val = ccw(b1, a, b2);
	return val == 0 && min(b1, b2) <= a && a <= max(b1, b2);
}

int networkFlow(int source, int sink, vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
	const int MAX_V = adj.size();
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
		int amount = INT32_MAX;
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

void addEdge(int s, int e, int c, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
	adj[s].push_back(e);
	adj[e].push_back(s);
	capacity[s][e] = c;
}

void solve() {
	int n, k, h, m; cin >> n >> k >> h >> m;
	vector<pair<ll, ll>> wall(n), holes(h), mice(m);
	for (int i = 0; i < n; ++i) cin >> wall[i].first >> wall[i].second;
	for (int i = 0; i < h; ++i) cin >> holes[i].first >> holes[i].second;
	for (int i = 0; i < m; ++i) cin >> mice[i].first >> mice[i].second;
	// source: m + h, mice: m, holes: m + h, sink: m + h + 1
	int MAX_V; MAX_V = m + h + 2;
	int source, sink; source = m + h, sink = m + h + 1;
	vector<vector<int>> adj(MAX_V);
	vector<vector<int>> capacity(MAX_V, vector<int>(MAX_V));
	vector<vector<int>> flow(MAX_V, vector<int>(MAX_V, 0));
	for (int i = 0; i < m; ++i) addEdge(source, i, 1, adj, capacity);
	for (int i = 0; i < m; ++i) for (int j = 0; j < h; ++j) {
		bool flag = true;
		for (int l = 0; l < n; ++l) {
			int nl = l + 1 == n ? 0 : l + 1;
			if (!isMeet(holes[j], wall[l], wall[nl]) && isMeet(mice[i], holes[j], wall[l], wall[nl])) {
				flag = false; break;
			}
		}
		if (flag) addEdge(i, m + j, 1, adj, capacity);
	}
	for (int i = 0; i < h; ++i) addEdge(m + i, sink, k, adj, capacity);
	auto ans = networkFlow(source, sink, adj, capacity, flow);
	if (ans == m) cout << "Possible";
	else cout << "Impossible";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}