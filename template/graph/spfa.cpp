#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
vector<pair<int, ll>> adj[MAX_V];

// time complexity: V+E
// empty vector: negative cycle
vector<ll> spfa(int src, int V) {
	vector<ll> dist(V, LLONG_MAX), cycleCnt(V, 0);
	vector<bool> inQ(V, false);
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