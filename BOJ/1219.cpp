#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> spfa(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX), cycleCnt(MAX_V, 0); vector<bool> inQ(MAX_V, false);
	vector<bool> skip(MAX_V, false);
	dist[src] = 0;
	queue<int> q;
	q.push(src); inQ[src] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop(); inQ[here] = false;
		for (auto [there, cost]: adj[here]) if (!skip[there] && dist[there] > dist[here] + cost) {
			dist[there] = dist[here] + cost;
			if (!inQ[there]) {
				++cycleCnt[there];
				if (cycleCnt[there] >= MAX_V) {
					skip[there] = true;
					dist[there] = LLONG_MIN;
					queue<int> tmpq; tmpq.push(there);
					while (!tmpq.empty()) {
						int tmp = tmpq.front(); tmpq.pop();
						for (auto [tmpt, _]: adj[tmp]) if (!skip[tmpt]) {
							skip[tmpt] = true;
							dist[tmpt] = LLONG_MIN;
							tmpq.push(tmpt);
						}
					}
				}
				q.push(there);
				inQ[there] = true;
			}
		}
	}
	return dist;
}

// time complexity: V+E
// 빈배열: 음의 사이클 존재
void solve() {
	int N, src, e, M; cin >> N >> src >> e >> M;
	int MAX_V = N;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<vector<ll>> edge;
	for (int i = 0; i < M; ++i) {
		ll a, b, c; cin >> a >> b >> c;
		edge.push_back({a, b, c});
	}
	vector<ll> earn(N);
	for (int i = 0; i < N; ++i) cin >> earn[i];
	for (int i = 0; i < M; ++i) {
		adj[edge[i][0]].push_back({edge[i][1], edge[i][2] - earn[edge[i][1]]});
	}
	vector<ll> ans = spfa(src, adj);
	if (ans[e] == LLONG_MAX) cout << "gg";
	else if (ans[e] == LLONG_MIN) cout << "Gee";
	else cout << -(ans[e] - earn[src]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}