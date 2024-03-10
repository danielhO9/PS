#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 빈배열: 음의 사이클 존재
// V: max vertex number
vector<ll> SPFA(int src, vector<vector<pair<int, ll>>>& adj, int V) {
	vector<ll> dist(V + 1, LLONG_MAX), cycleCnt(V + 1, 0); vector<bool> inQ(V + 1, false);
	dist[src] = 0;
	queue<int> q;
	q.push(src); inQ[src] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop(); inQ[here] = false;
		for (auto [there, cost]: adj[here]) if (dist[there] > dist[here] + cost) {
			dist[there] = dist[here] + cost;
			if (!inQ[there]) {
				++cycleCnt[there];
				if (cycleCnt[there] >= V) return {};
				q.push(there);
				inQ[there] = true;
			}
		}
	}
	return dist;
}

void solve() {
	// N: max number
	int N;
	vector<vector<pair<int, ll>>> adj(N + 1);
	vector<ll> ans = SPFA(1, adj, N);
}