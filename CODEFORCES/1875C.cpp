#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL x, LL y){
	if (x < y) swap(x, y);
	if (y == 0) return x;
	return gcd(y, x % y);
}

void solve() {
	LL n, m; cin >> n >> m;
	n %= m;
	if (n == 0) {
		cout << 0 << '\n';
		return;
	}
	LL g = gcd(n, m);
	n /= g; m /= g;
	LL temp = m, k = 0;
	while (true) {
		if (temp == 1) break;
		if (temp % 2 == 1) {
			cout << -1 << '\n';
			return;
		}
		temp /= 2;
		++k;
	}
	LL ans = 0;
	vector<LL> cnt(k + 1, 0);
	for (LL i = 0; i < k; ++i) {
		if (n == (n | (1LL << i))) cnt[i] += m;
	}
	for (LL i = 0; i < k; ++i) {
		ans += cnt[i] / 2;
		cnt[i + 1] += cnt[i] / 2;
	}
	ans *= g; cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}