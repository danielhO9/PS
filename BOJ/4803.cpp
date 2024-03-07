#include <bits/stdc++.h>
using namespace std;
int n, m;

void solve() {
	vector<int> adj[n + 1];
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int cnt = 0;
	bool vis[n + 1]; memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		bool isTree = true;
		deque<pair<int, int>> Q; Q.push_back(make_pair(i, 0)); vis[i] = true;
		while (!Q.empty()) {
			auto here = Q.front().first, p = Q.front().second; Q.pop_front();
			for (auto there: adj[here]) if (there != p) {
				if (vis[there]) isTree = false;
				else {
					vis[there] = true;
					Q.push_back(make_pair(there, here));
				}
			}
		}
		if (isTree) ++cnt;
	}
	if (cnt == 0) {
		cout << "No trees.\n";
	} else if (cnt == 1) {
		cout << "There is one tree.\n";
	} else {
		cout << "A forest of " << cnt << " trees.\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int cnt = 0;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		cout << "Case " << ++cnt << ": ";
		solve();
	}
}