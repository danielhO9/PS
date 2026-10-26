#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[200001];
int cache[200001][3][2];
int par[200001];
int sz[200001];

int matchCache(int v, int x, int cut) {
	int& ret = cache[v][x][cut];
	if (ret != -1) return ret;
	
	int cnt = 0;
	for (auto u: adj[v]) if (u != par[v]) ++cnt;

	if (x == 0) {
		if (cut == 1) return ret = -987654321;
		else return ret = 1;
	}

	if (x == 1) {
		if (cut) return ret = cnt;

		ret = 0;
		for (auto u: adj[v]) if (u != par[v]) {
			ret = max(ret, matchCache(u, 1, 1) + 1);
			ret = max(ret, matchCache(u, 1, 0));
		}
		return ret;
	}
	if (sz[v] < 2) return ret = -987654321;
	if (cut) {
		ret = 0;
		for (auto u: adj[v]) if (u != par[v]) ret = max(ret, cnt - 1 + max(matchCache(u, 1, 1), matchCache(u, 1, 0)));
		return ret;
	}
	else {
		ret = 0;
		for (auto u: adj[v]) if (u != par[v]) ret = max(ret, matchCache(u, 2, 0));
		for (auto u: adj[v]) if (u != par[v]) ret = max(ret, matchCache(u, 2, 1) + 1);
		if (cnt >= 2) {
			vector<int> tmp;
			for (auto u: adj[v]) if (u != par[v]) {
				tmp.push_back(max(matchCache(u, 1, 1), matchCache(u, 1, 0) - 1));
			}
			sort(tmp.begin(), tmp.end());
			reverse(tmp.begin(), tmp.end()); tmp.resize(2);
			ret = max(ret, tmp[0] + tmp[1] + 1);
		}
		return ret;
	}

}

void dfs(int v, int p) {
	par[v] = p;
	sz[v] = 1;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		sz[v] += sz[u];
	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) for (int j = 0; j <= 2; ++j) for (int k = 0; k < 2; ++k) cache[i][j][k] = -1;
	vector<int> ans;
	for (int j = 0; j < 2; ++j) ans.push_back(matchCache(1, 2, j));
	cout << *max_element(ans.begin(), ans.end()) << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}