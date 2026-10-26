#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	vector<LL> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	LL ans = 2LL;
	vector<bool> check(2);
	while (true) {
		for (int j = 0; j < 2; ++j) check[j] = 0;
		for (int i = 0; i < n; ++i) {
			check[a[i] % 2] = 1;
			a[i] /= 2;
		}
		if (check[0] && check[1]) {
			cout << ans << '\n';
			return;
		}
		ans *= 2;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}