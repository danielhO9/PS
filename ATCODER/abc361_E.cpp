#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int, ll>> adj[200001];
ll maxd = 0ll, maxv;

void dfs(int v, ll d, int p) {
	if (maxd < d) {
		maxd = d; maxv = v;
	}
	for (auto [i, j]: adj[v]) if (i != p) dfs(i, d + j, v);
}

void solve() {
	int N; cin >> N;
	ll sum = 0ll;
	for (int i = 0; i < N - 1; ++i) {
		int a, b; ll c; cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
		sum += c;
	}
	dfs(1, 0, 0); maxd = 0ll; dfs(maxv, 0, 0);
	sum -= maxd;
	ll ans = sum * 2 + maxd;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}