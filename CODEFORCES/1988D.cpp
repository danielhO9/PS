#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[300001];
ll cache[300001][20];
vector<int> adj[300001];

ll matchCache(int v, int c, int p) {
	ll& ret = cache[v][c];
	if (ret != -1) return ret;
	ret = a[v] * c;
	for (auto u: adj[v]) if (u != p) {
		ll minv = LLONG_MAX;
		for (int i = 1; i < 20; ++i) if (i != c) {
			minv = min(minv, matchCache(u, i, v));
		}
		ret += minv;
	}
	return ret;
}

void solve() {
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < 20; ++j) cache[i][j] = -1;
		adj[i].clear();
	}
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 0; i < n - 1; ++i) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	ll ans = LLONG_MAX;
	for (int i = 1; i < 20; ++i) ans = min(ans, matchCache(1, i, 0));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}