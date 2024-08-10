#include <bits/stdc++.h>
using namespace std;

vector<int> adj[2001];
int male[2001];

void solve() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < m; ++i) {
		int v, u; cin >> v >> u;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}
	for (int i = 1; i <= n; ++i) male[i] = -1;
	for (int i = 1; i <= n; ++i) {
		if (male[i] != -1) continue;
		male[i] = 1; queue<int> q; q.push(i);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there: adj[here]) {
				if (male[there] == male[here]) {
					cout << "Suspicious bugs found!\n";
					return;
				}
				if (male[there] == -1) {
					male[there] = 1 - male[here];
					q.push(there);
				}
			}
		}
	}
	cout << "No suspicious bugs found!\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Scenario #" << i << ":\n";
		solve();
		cout << '\n';
	}
}