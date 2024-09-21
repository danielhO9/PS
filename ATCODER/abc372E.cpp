#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
vector<int> adj[200001];
int par[200001];

int find(int x) {
	if (par[x] == x) return x;
	par[x] = find(par[x]);
	return par[x];
}

void solve() {
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) adj[i].push_back(-i);
	for (int i = 1; i <= N; ++i) par[i] = i;
	while (Q--) {
		int t, u, v; cin >> t >> u >> v;
		if (t == 1) {
			u = find(u); v = find(v);
			if (u == v) continue;
			if (adj[u].size() < adj[v].size()) swap(u, v);
			par[v] = u;
			for (auto i: adj[v]) {
				adj[u].push_back(i);
			}
			sort(adj[u].begin(), adj[u].end());
			vector<int> tmp = vector<int>(adj[u].begin(), adj[u].end());
			adj[u].clear();
			for (auto i: tmp) {
				if (adj[u].empty() || adj[u].back() != i) adj[u].push_back(i);
			}
			while (adj[u].size() > 10) adj[u].pop_back();
		} else {
			u = find(u);
			if (adj[u].size() < v) {
				cout << -1 << '\n';
			} else {
				cout << -adj[u][v - 1] << '\n';
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}