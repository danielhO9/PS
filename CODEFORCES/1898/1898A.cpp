#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;
	int cnt = 0;
	for (auto i: s) if (i == 'B') ++cnt;
	int ans = 0;
	if (cnt > k) {
		for (auto i: s) {
			++ans;
			if (i == 'B') {
				--cnt;
				if (cnt == k) break;
			}
		}
		cout << 1 << '\n' << ans << ' ' << 'A' << '\n';
	} else if (cnt < k) {
		for (auto i: s) {
			++ans;
			if (i == 'A') {
				++cnt;
				if (cnt == k) break;
			}
		}
		cout << 1 << '\n' << ans << ' '  << 'B' << '\n';
	} else {
		cout << 0 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}