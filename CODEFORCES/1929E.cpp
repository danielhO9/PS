#include <bits/stdc++.h>
using namespace std;
int n, k;

void dfs(int v, int p, vector<vector<int>>& adj, vector<int>& dep, vector<int>& par) {
	par[v] = p; dep[v] = dep[p] + 1;
	for (auto i: adj[v]) if (i != p) dfs(i, v, adj, dep, par);
}

int matchCache(int x, vector<int>& cache, vector<int>& mask, vector<vector<int>>& avail) {
	if (x == (1 << k) - 1) return 0;
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = 987654321;
	int t = 0;
	for (int i = 0; i < k; ++i) {
		if ((x >> i) & 1) continue;
		else {
			t = i; break;
		}
	}
	for (auto i: avail[t]) {
		ret = min(ret, matchCache(x | mask[i], cache, mask, avail) + 1);
	}
	return ret;
}

void solve() {
	cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> dep(n + 1), par(n + 1), mask(n + 1);
	dfs(1, 0, adj, dep, par);
	cin >> k;
	vector<vector<int>> avail(k);
	for (int i = 0; i < k; ++i) {
		int a, b; cin >> a >> b;
		while (a != b) {
			if (dep[a] > dep[b]) {
				mask[a] |= (1 << i);
				avail[i].push_back(a);
				a = par[a];
			}
			else {
				mask[b] |= (1 << i);
				avail[i].push_back(b);
				b = par[b];
			}
		}
	}
	vector<int> cache(1 << k, -1);
	cout << matchCache(0, cache, mask, avail) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}