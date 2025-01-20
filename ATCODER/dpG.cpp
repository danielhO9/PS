#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100001];
int deg[100001];
int cache[100001];
int N, M;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		++deg[y];
	}
	queue<int> q;
	for (int i = 1; i <= N; ++i) if (deg[i] == 0) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto v: adj[u]) {
			cache[v] = max(cache[v], cache[u] + 1);
			--deg[v];
			if (deg[v] == 0) q.push(v);
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; ++i) ans = max(ans, cache[i]);
	cout << ans;
}