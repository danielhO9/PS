#include <bits/stdc++.h>
using namespace std;

int N, K, A, B;
unordered_set<int> adj[500001];
int dis[500001], ndis[500001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K >> A >> B;
	for (int i = 0; i < K; ++i) {
		int u, v; cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	for (int i = 1; i <= N; ++i) ndis[i] = INT32_MAX;
	queue<int> q; q.push(1); ndis[1] = 0;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (auto there: adj[here]) if (ndis[there] == INT32_MAX) {
			ndis[there] = ndis[here] + A;
			q.push(there);
		}
	}
	q.push(1); dis[1] = 0;
	for (int i = 2; i <= N; ++i) dis[i] = INT32_MAX;
	queue<int> unvis; for (int i = 2; i <= N; ++i) unvis.push(i);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		queue<int> nunvis;
		while (!unvis.empty()) {
			int there = unvis.front(); unvis.pop();
			if (adj[here].find(there) == adj[here].end()) {
				dis[there] = dis[here] + B;
				q.push(there);
			} else nunvis.push(there);
		}
		swap(nunvis, unvis);
	}
	cout << min(dis[N], ndis[N]);

}