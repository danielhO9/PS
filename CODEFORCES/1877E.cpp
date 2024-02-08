#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a(200001);
unordered_map<int, vector<int>> M;
vector<int> ans(200001, -1);
vector<int> degree(200001, 0);

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		M[a[i]].push_back(i);
		++degree[a[i]];
	}
	queue<int> Q;
	vector<bool> visited(n + 1, 0);
	for (int i = 1; i <= n; ++i) if (degree[i] == 0) { Q.push(i); visited[i] = 1; }
	while (!Q.empty()) {
		int f = Q.front(); Q.pop();
		int temp = 1;
		for (auto i: M[f]) if (ans[i] == 1) temp = 0;
		ans[f] = temp;
		--degree[a[f]];
		if ((degree[a[f]] == 0 || ans[f] == 1) && !visited[a[f]]) {
			Q.push(a[f]); visited[a[f]] = 1;
		}
	}
	// for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	for (int i = 1; i <= n; ++i) {
		if (ans[i] == -1) {
			int v = i, cyc = 0, t = 1;
			while (true) {
				if (ans[v] != -1) break;
				ans[v] = t;
				++cyc; t ^= 1;
				v = a[v];
			}
			if (cyc % 2 == 1) {
				cout << -1;
				return;
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) if (ans[i]) ++cnt;
	cout << cnt << '\n';
	for (int i = 1; i <= n; ++i) if (ans[i]) cout << a[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}