#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	LL a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	LL mina[n], ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) mina[i] = a[i];
		else {
			LL temp = (a[i] + mina[i + 1] - 1) / mina[i + 1];
			ans += temp - 1;
			a[i] /= temp;
			mina[i] = min(a[i], mina[i + 1]);
		}
	}
	cout << ans << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}