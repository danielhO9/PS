#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	int b[n]; for (int i = 0; i < n; ++i) cin >> b[i];
	bool visited[n];
	for (int i = 0; i < n; ++i) visited[i] = 0;
	int lastIndex = n - 1, cnt = 0;
	while (true) {
		if (b[lastIndex] <= n) {
			++cnt;
			visited[lastIndex] = 1;
			lastIndex -= b[lastIndex];
			if (lastIndex < 0) lastIndex += n;
			if (cnt == k || visited[lastIndex] == 1) {
				cout << "YES" << '\n';
				return;
			}
		} else {
			break;
		}
	}
	cout << "NO" << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}