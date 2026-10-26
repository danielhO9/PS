#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;
LL two[100001];

void solve() {
	LL n; cin >> n;
	vector<LL> a(n + 1, 0); for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<LL> b(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		LL ans = a[i];
		for (int j = 1; j <= n / i; ++j) ans = max(ans, a[i * j]);
		b[i] = ans;
	}
	for (LL i = 0; i <= 1e5; ++i) {
		if (i == 0) two[i] = 1;
		else {
			two[i] = two[i - 1] * 2;
			two[i] %= MOD;
		}
	}
	LL ans = 0;
	vector<LL> V;
	for (int i = 1; i <= n; ++i) V.push_back(b[i]);
	sort(V.begin(), V.end());
	for (LL i = n - 1; i >= 0; --i) {
		ans += V[i] * two[i];
		ans %= MOD;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}