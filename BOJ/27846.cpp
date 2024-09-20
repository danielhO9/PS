#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, Tc, Tm;
ll a[100], b[100], c[100];

bool f(ll x) {
	ll mn = max(1ll, Tc - x), mx = min(Tc + Tm - x - 1, Tc);
	for (int i = 0; i < N; ++i) {
		if (a[i] > b[i]) {
			if (c[i] - b[i] * (Tc + Tm - x) > 0) mx = min(mx, (c[i] - b[i] * (Tc + Tm - x)) / (a[i] - b[i]));
			else mx = min(mx, (c[i] - b[i] * (Tc + Tm - x) - (a[i] - b[i] - 1)) / (a[i] - b[i]));
		} else if (a[i] < b[i]) {
			if (b[i] * (Tc + Tm - x) - c[i] < 0) mn = max(mn, (b[i] * (Tc + Tm - x) - c[i]) / (b[i] - a[i]));
			else mn = max(mn, (b[i] * (Tc + Tm - x) - c[i] + b[i] - a[i] - 1) / (b[i] - a[i]));
		} else {
			if (c[i] - b[i] * (Tc + Tm - x) < 0) return false;
		}
	}
	// cout << x << ' ' << mn << ' ' << mx << '\n';
	return mn <= mx;
}

void solve() {
	cin >> N >> Tc >> Tm;
	for (int i = 0; i < N; ++i) cin >> a[i] >> b[i] >> c[i];
	ll l = -1, r = Tc + Tm - 2;
	while (l + 1 < r) {
		ll mid = (l + r) / 2;
		if (f(mid)) r = mid;
		else l = mid;
	}
	cout << r << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}