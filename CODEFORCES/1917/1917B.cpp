#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> V(n);
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		V[i] = c - 'a';
	}
	vector<bool> visited(26, 0);
	int ans = 0, cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (!visited[V[i]]) {
			++cnt;
			visited[V[i]] = 1;
		}
		ans += cnt;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}