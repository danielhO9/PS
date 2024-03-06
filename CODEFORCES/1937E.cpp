#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dijkstra(int src, vector<vector<pair<int, ll>>>& adj, int V) {
	vector<ll> dist(V, LLONG_MAX);
	dist[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int n, m;

void solve() {
	cin >> n >> m;
	vector<ll> c(n + 1); for (int i = 1; i <= n; ++i) cin >> c[i];
	vector<vector<ll>> a(n + 1, vector<ll>(m + 1));
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
	int tot = n;
	vector<vector<pair<int, ll>>> adj((n + 1) * (m + 1));
	vector<vector<int>> id(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		id[i][j] = ++tot;
		adj[tot].push_back(make_pair(i, c[i]));
		adj[i].push_back(make_pair(tot, 0ll));
	}
	int ord[n + 1];
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) ord[i] = i;
		sort(ord + 1, ord + n + 1, [&] (int x, int y) { return a[x][j] < a[y][j]; });
		for (int i = 1; i < n; ++i) {
			adj[id[ord[i]][j]].push_back(make_pair(id[ord[i + 1]][j], 0ll));
			adj[id[ord[i + 1]][j]].push_back(make_pair(id[ord[i]][j], a[ord[i + 1]][j] - a[ord[i]][j]));
		}
	}
	vector<ll> ans = dijkstra(1, adj, ++tot);
	cout << ans[n] << '\n';
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}