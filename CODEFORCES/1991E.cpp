#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[10001];
int col[10001];

bool dfs(int v, int p) {
	bool ret = true;
	for (auto u: adj[v]) if (u != p) {
		if (col[u] == -1) {
			col[u] = 1 - col[v];
			if (!dfs(u, v)) ret = false;
		} else {
			if (col[u] == col[v]) {
				ret = false;
			}
		}
	}
	return ret;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i <= n; ++i) col[i] = -1;
	for (int i = 0; i < m; ++i) {
		int v, u; cin >> v >> u;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	col[1] = 1;
	bool bob = dfs(1, 0);
	if (bob) cout << "Bob" << endl;
	else cout << "Alice" << endl;
	if (bob) {
		vector<int> one, two;
		for (int i = 1; i <= n; ++i) {
			if (col[i] == 1) one.push_back(i);
			else two.push_back(i);
		}
		for (int i = 1; i <= n; ++i) {
			int a, b; cin >> a >> b;
			if (a > b) swap(a, b);
			if (a == 1) {
				if (one.empty()) {
					cout << two.back() << ' ' << b << endl;
					two.pop_back();
				} else {
					cout << one.back() << ' ' << a << endl;
					one.pop_back();
				}
			} else {
				if (two.empty()) {
					cout << one.back() << ' ' << b << endl;
					one.pop_back();
				} else {
					cout << two.back() << ' ' << a << endl;
					two.pop_back();
				}
			}
		}
	} else {
		for (int i = 0; i < n; ++i) {
			cout << 1 << ' ' << 2 << endl;
			int a, b; cin >> a >> b;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}