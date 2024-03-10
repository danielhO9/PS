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
	int N, M; cin >> N >> M;
	vector<vector<pair<int, ll>>> adj(N + 1);
	while (M--) {
		int A, B; ll C; cin >> A >> B >> C;
		adj[A].push_back({B, C});
	}
	vector<ll> ans = SPFA(1, adj, N);
	if (ans.size() == 0) {
		cout << -1; return;
	}
	for (int i = 2; i <= N; ++i) {
		if (ans[i] == LLONG_MAX) cout << -1 << '\n';
		else cout << ans[i] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}