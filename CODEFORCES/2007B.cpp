#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[100001];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll mx = 0;
	for (int i = 0; i < n; ++i) mx = max(mx, a[i]);
	for (int i = 0; i < m; ++i) {
		char t; ll l, r; cin >> t >> l >> r;
		if (t == '+') {
			if (l <= mx && mx <= r) ++mx;
		} else {
			if (l <= mx && mx <= r) --mx;
		}
		cout << mx << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}