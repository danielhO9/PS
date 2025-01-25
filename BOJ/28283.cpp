#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M, X, Y;
ll A[500001];
vector<int> adj[500001];
vector<int> B;
ll vis[500001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> X >> Y;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = 0; i < M; ++i) {
		int s, e; cin >> s >> e;
		adj[s].push_back(e);
		adj[e].push_back(s);
	}
	for (int i = 0; i < Y; ++i) {
		int visp; cin >> visp;
		B.push_back(visp);
	}
	memset(vis, -1, sizeof(vis));
	queue<int> q;
	for (auto i: B) {
		q.push(i);
		vis[i] = 0;
	}
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (auto there: adj[here]) if (vis[there] == -1) {
			vis[there] = vis[here] + 1;
			q.push(there);
		}
	}
	for (int i = 1; i <= N; ++i) if (vis[i] == -1 && A[i] > 0) {
		cout << -1;
		return 0;
	}
	priority_queue<ll> pq;
	for (int i = 1; i <= N; ++i) {
		pq.push(vis[i] * A[i]);
	}
	ll ans = 0;
	while (X--) {
		ans += pq.top(); pq.pop();
	}
	cout << ans;
}