#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string, ll> dijkstra(string src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	map<string, ll> dist;
	dist[src] = 0;
	priority_queue<pair<ll, string>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		string here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;

		for (int l = 0; l < MAX_V; ++l) {
			for (auto [r, c]: adj[l]) {
				string there = here;
				swap(there[l], there[r]);
				ll nextDist = cost + c;
				if (dist.find(there) == dist.end() || dist[there] > nextDist) {
					dist[there] = nextDist;
					pq.push(make_pair(-nextDist, there));
				}
			}
		}
	}
	return dist;
}

void solve() {
	int N; cin >> N;
	string A;
	for (int i = 0; i < N; ++i) {
		int tmp; cin >> tmp;
		A += 'a' + tmp;
	}
	string sorted = A;
	sort(sorted.begin(), sorted.end());
	int M; cin >> M;
	vector<vector<pair<int, ll>>> adj(N);
	for (int i = 0; i < M; ++i) {
		int l, r; ll c;
		cin >> l >> r >> c; --l; --r;
		adj[l].push_back({r, c});
		adj[r].push_back({l, c});
	}
	map<string, ll> ans = dijkstra(A, adj);
	if (ans.find(sorted) == ans.end()) {
		cout << -1;
	} else cout << ans[sorted];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}