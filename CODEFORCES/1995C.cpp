#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[200000];
ll ans[200000];

void solve() {
	cin >> n;
	ans[0] = 0;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 1; i < n; ++i) {
		if (a[i - 1] > 1 && a[i] == 1) {
			cout << -1 << '\n';
			return;
		}
		if (a[i - 1] == 1) {
			ans[i] = 0;
			continue;
		}
		ans[i] = ans[i - 1] + log2( log(a[i - 1]) / (double) log(a[i]) ); --ans[i];
		ans[i] = max(ans[i], 0ll);
		while (ans[i - 1] + log2(log(a[i - 1])) - 1e-7 > ans[i] + log2(log(a[i]))) {
			++ans[i];
		}
	}
	ll cnt = 0;
	for (int i = 0; i < n; ++i) cnt += ans[i];
	// for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
	cout << cnt << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}