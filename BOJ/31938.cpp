#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;

vector<pair<int, ll>> adj[200001];
ll par[200001];

vector<ll> dijkstra(int src) {
	const int MAX_V = N + 1;
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
			if (dist[there] >= nextDist) {
				if (dist[there] > nextDist) {
					par[there] = adj[here][i].second/9ll;
					dist[there] = nextDist;
					pq.push(make_pair(-nextDist, there));
				}
				else if (par[there] > adj[here][i].second/9) par[there] = adj[here][i].second/9ll;
			}
		}
	}
	return dist;
}

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b; ll c;
		cin >> a >> b >> c;
		c = c * 9 / 10;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	for (int i = 1; i <= N; ++i) par[i] = LLONG_MAX;
	vector<ll> dist = dijkstra(1);
	ll ans = 0;
	for (int i = 1; i <= N; ++i) ans += dist[i];
	for (int i = 2; i <= N; ++i) ans += par[i];
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}