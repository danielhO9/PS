#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll B[100001];
ll C[100001];
ll L[100001];
priority_queue<ll> pq[100001];
ll m[100001];
vector<int> adj[100001];
ll ans = 0ll;

void dfs(int v) {
	pq[v].push(C[v]);
	m[v] += C[v];
	for (auto u: adj[v]) {
		dfs(u);
		if (pq[v].size() < pq[u].size()) {
			swap(pq[u], pq[v]);
			swap(m[u], m[v]);
		}
		while (!pq[u].empty()) {
			pq[v].push(pq[u].top());
			m[v] += pq[u].top();
			pq[u].pop();
		}
	}
	while (m[v] > M) {
		m[v] -= pq[v].top();
		pq[v].pop();
	}
	ans = max(ans, L[v] * (ll) pq[v].size());
	// cout << v << ' ' << pq[v].size() << '\n';
}

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> B[i] >> C[i] >> L[i];
		adj[B[i]].push_back(i);
	}
	dfs(1);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}