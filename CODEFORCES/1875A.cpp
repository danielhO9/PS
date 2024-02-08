#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL a, b, n; cin >> a >> b >> n;
	LL ans = b;
	LL x[n]; for (int i = 0; i < n; ++i) {
		cin >> x[i];
		x[i] = min(x[i], a - 1);
		ans += x[i];
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}