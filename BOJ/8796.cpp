#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<int> adj[1000001];
int dis[1000001];
int cnt[1000000];

void solve() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) adj[i].clear();
	while (M--) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
	dis[1] = 0; queue<int> q; q.push(1);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		++cnt[dis[here]];
		for (auto there: adj[here]) if (dis[there] == INT32_MAX) {
			q.push(there);
			dis[there] = dis[here] + 1;
		}
	}
	for (int i = 1; i < N; ++i) if (cnt[i] > K) {
		cout << i << '\n';
		return;
	}
	cout << "hurray!\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}