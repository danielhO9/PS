#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int V, E; cin >> V >> E;
	vector<vector<ll>> dis(V + 1, vector<ll>(V + 1, INT32_MAX));
	for (int i = 0; i < E; ++i) {
		int a, b; ll c; cin >> a >> b >> c;
		dis[a][b] = min(dis[a][b], c);
	}
	for (int i = 1; i <= V; ++i) dis[i][i] = 0ll;
	for (int m = 1; m <= V; ++m) for (int s = 1; s <= V; ++s) for (int e = 1; e <= V; ++e) {
		if (dis[s][e] > dis[s][m] + dis[m][e]) dis[s][e] = dis[s][m] + dis[m][e];
	}
	ll ans = LLONG_MAX;
	for (int i = 1; i <= V; ++i) for (int j = 1; j <= V; ++j) {
		if (i != j) ans = min(ans, dis[i][j] + dis[j][i]);
	}
	if (ans >= INT32_MAX) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}