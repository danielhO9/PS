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

void solve() {
	int n, m, t; cin >> n >> m >> t;
	int s, g, h; cin >> s >> g >> h;
	vector<vector<pair<int, ll>>> adj(n + 1);
	ll e;
	while (m--) {
		int a, b; ll d; cin >> a >> b >> d;
		adj[a].push_back(make_pair(b, d));
		adj[b].push_back(make_pair(a, d));
		if (a == min(g, h) && b == max(g, h)) e = d;
	}
	vector<int> tar(t);
	for (int i = 0; i < t; ++i) cin >> tar[i];
	vector<ll> sdis = dijkstra(s, adj, n + 1);
	vector<ll> gdis = dijkstra(g, adj, n + 1);
	vector<ll> hdis = dijkstra(h, adj, n + 1);
	vector<int> ans;
	for (int i: tar) {
		if (sdis[i] == sdis[g] + e + hdis[i] || sdis[i] == sdis[h] + e + gdis[i]) {
			ans.push_back(i);
		}
	}
	sort(ans.begin(), ans.end());
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}