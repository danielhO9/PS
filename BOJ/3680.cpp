#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<tuple<ll, ll, ll>, int> m;

vector<ll> spfa(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX), cycleCnt(MAX_V, 0); vector<bool> inQ(MAX_V, false);
	dist[src] = 0;
	queue<int> q;
	q.push(src); inQ[src] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop(); inQ[here] = false;
		for (auto [there, cost]: adj[here]) if (dist[there] > dist[here] + cost) {
			dist[there] = dist[here] + cost;
			if (!inQ[there]) {
				++cycleCnt[there];
				if (cycleCnt[there] >= MAX_V) return {};
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
	m.clear();
	
	int MAX_V;
	int src;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<ll> ans = spfa(src, adj);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}