#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> b(n + 1);
	vector<int> deg(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		++deg[b[i]];
	}
	if (k == 1) {
		for (int i = 1; i <= n; ++i) if (b[i] != i) {
			cout << "NO\n"; return;
		}
		cout << "YES\n"; return;
	}
	deque<int> Q;
	for (int i = 1; i <= n; ++i) if (deg[i] == 0) Q.push_back(i);
	while (!Q.empty()) {
		int here = Q.front(); Q.pop_front();
		int there = b[here]; --deg[there];
		if (deg[there] == 0) Q.push_back(there);
	}
	vector<bool> vis(n + 1, false);
	for (int i = 1; i <= n; ++i) if (deg[i] == 0) vis[i] = true;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		int here = i, cnt = 0;
		while (!vis[here]) {
			vis[here] = true;
			++cnt;
			here = b[here];
		}
		if (cnt != k) {
			cout << "NO\n"; return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}