#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> adj[100001];
int a[100001];
int b[100001];
bool vis[100001];
double val[100001];
int par[100001];
const double MAX = 3.141592;

bool dfs(int v, int p, int idx) {
	bool ret = true;
	for (auto u: adj[v]) if (u.first != p) {
		int na = -a[v];
		int nb = u.second - b[v];
		par[u.first] = idx;

		if (vis[u.first]) {
			if (na == a[u.first]) {
				if (nb == b[u.first]) continue;
				else return false;
			}
			double x = (double) (b[u.first] - nb) / (na - a[u.first]);
			if (val[idx] == MAX) val[idx] = x;
			else {
				if (abs(val[idx] - x) < 1e-4) continue;
				else return false;
			}
		} else {
			a[u.first] = na;
			b[u.first] = nb;
			vis[u.first] = true;
			if (dfs(u.first, v, idx)) ret = false;
		}

	}
	return ret;
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int u, v, t; cin >> u >> v >> t;
		adj[u].push_back({v, t});
		adj[v].push_back({u, t});
	}
	for (int i = 1; i <= N; ++i) if (!vis[i]) {
		a[i] = 1; b[i] = 0; par[i] = i; val[i] = MAX;
		if (!dfs(i, 0, i)) cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}