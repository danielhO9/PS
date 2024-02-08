#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n;

LL getSz(int v, int p, vector<LL>& sz, vector<vector<pair<int, LL>>>& graph) {
	sz[v] = 1;
	for (auto [i, _]: graph[v]) if (i != p) {
		sz[v] += getSz(i, v, sz, graph);
	}
	return sz[v];
}

LL matchCache(vector<LL>& cache, int v, int p, vector<vector<pair<int, LL>>>& graph, vector<LL>& sz) {
	LL& ret = cache[v];
	if (ret != -1) return ret;
	ret = 0;
	for (auto [u, d]: graph[v]) if (u != p) {
		ret += matchCache(cache, u, v, graph, sz) + d * sz[u];
	}
	return ret;
}

void getAns(int v, int p, vector<vector<pair<int, LL>>>& graph, vector<LL>& sz, vector<LL>& ans) {
	for (auto [u, d]: graph[v]) if (u != p) {
		ans[u] = ans[v] + (n - 2 * sz[u]) * d;
		getAns(u, v, graph, sz, ans);
	}
}

void solve() {
	vector<vector<pair<int, LL>>> graph(n);
	int a, b; LL w;
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b >> w;
		graph[a].push_back({b, w});
		graph[b].push_back({a, w});
	}
	vector<LL> sz(n); getSz(0, -1, sz, graph);
	vector<LL> cache(n, -1);
	vector<LL> ans(n);
	ans[0] = matchCache(cache, 0, -1, graph, sz); getAns(0, -1, graph, sz, ans);
	cout << *min_element(ans.begin(), ans.end()) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> n;
		if (n == 0) break;
		solve();
	}
}