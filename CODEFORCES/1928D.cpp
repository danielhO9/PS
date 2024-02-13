#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, b, x;

LL f(LL cnt, vector<LL>& c) {
	LL ans = 0;
	for (auto i: c) {
		LL m = i / cnt, M = i % cnt;
		LL temp = i * (i - 1) / 2;
		temp -= ((m + 1) * m / 2) * M;
		if (m >= 1) temp -= (m * (m - 1) / 2) * (cnt - M);
		ans += temp;
	}
	ans *= b;
	ans -= (cnt - 1) * x;
	return ans;
}

void solve() {
	cin >> n >> b >> x;
	LL l = 1, r = 0, mid1, mid2;
	vector<LL> c(n);
	for (int i = 0; i < n; ++i) {
		cin >> c[i];
		r = max(r, c[i]);
	}
	while (r - l >= 3) {
		mid1 = (l * 2 + r) / 3, mid2 = (l + r * 2) / 3;
		if (f(mid1, c) >= f(mid2, c)) r = mid2;
		else l = mid1;
	}
	LL ans = LLONG_MIN;
	for (LL i = l; i <= r; ++i) ans = max(ans, f(i, c));
	cout << ans << '\n';
	// cout << f(3, c);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}