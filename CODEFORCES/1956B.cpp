#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	int ans = 0;
	vector<int> cnt(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		int c; cin >> c;
		++cnt[c];
		if (cnt[c] == 2) ++ans;
	}
	cout << ans << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}