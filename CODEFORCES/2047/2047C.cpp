#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[2][5000];
ll mn[5000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[0][i];
	for (int i = 0; i < n; ++i) cin >> a[1][i];
	for (int i = 0; i < n; ++i) {
		mn[i] = min(a[0][i], a[1][i]);
	}
	ll smmx = *max_element(mn, mn + n);
	int idx = -1;
	for (int i = 0; i < n; ++i) if (mn[i] == smmx) {
		idx = i;
		break;
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) if (i != idx) ans += max(a[0][i], a[1][i]);
	ans += a[0][idx] + a[1][idx];
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}