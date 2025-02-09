#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dijkstra(vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX);
	priority_queue<pair<ll, int>> pq;
	int cur = 1, val = 1;
	while (cur <= 100000) {
		pq.push({-val, cur + 100000});
		dist[cur + 100000] = val;
		cur *= 2;
		++val;
	}
	cur = -1, val = 1;
	while (cur >= -100000) {
		pq.push({-val, cur + 100000});
		dist[cur + 100000] = val;
		cur *= 2;
		++val;
	}
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

// MAX_V: max vertex number
// time complexity: (V+E)logV
// -100000 ~ 100000
void solve() {
	int MAX_V = 200001;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	for (int i = -100000; i <= 100000; ++i) {
		int cur = i;
		int add = 1, val = 1;
		while (cur + add <= 100000) {
			adj[i + 100000].push_back({cur + add + 100000, val + 4});
			add *= 2;
			++val;
		}
		cur = i;
		add = -1, val = 1;
		while (cur + add >= -100000) {
			adj[i + 100000].push_back({cur + add + 100000, val + 4});
			add *= 2;
			++val;
		}
	}
	vector<ll> ans = dijkstra(adj);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << ans[n + 100000] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}