#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dijkstra(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX);
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

int n, k;

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	cin >> n >> k;
	int MAX_V = n + 1;
	ll a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<pair<ll, int>> v;
	for (int i = 1; i <= n; ++i) v.push_back({a[i], i});
	sort(v.begin(), v.end());
	for (int i = 0; i + 1 < n; ++i) {
		int u = v[i].second, nu = v[i + 1].second;
		adj[u].push_back({nu, a[nu] - a[u]});
		adj[nu].push_back({u, a[nu] - a[u]});
	}
	for (int i = 0; i < k; ++i) {
		int u, nu; cin >> u >> nu;
		adj[u].push_back({nu, 0});
		adj[nu].push_back({u, 0});
	}
	
	vector<ll> ans = dijkstra(1, adj);
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}