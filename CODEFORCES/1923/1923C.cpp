#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, q; cin >> n >> q;
	vector<ll> c(n + 1, 0);
	for (int i = 1; i <= n; ++i) cin >> c[i];
	vector<ll> ocnt(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		if (c[i] == 1) ocnt[i] = 1;
		ocnt[i] += ocnt[i - 1];
	}
	
	vector<ll> sum(n + 1, 0);
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + c[i];
	while (q--) {
		ll l, r; cin >> l >> r;
		ll qsum = sum[r] - sum[l - 1];
		ll qone = ocnt[r] - ocnt[l - 1];
		ll cnt = r - l + 1;
		if (cnt + qone <= qsum && cnt != 1) {
			cout << "YES\n";
		} else cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}