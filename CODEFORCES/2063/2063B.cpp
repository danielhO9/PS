#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, l, r;
ll a[100000];

void solve() {
	cin >> n >> l >> r; --l; --r;
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll ans = 0;
	for (int i = l; i <= r; ++i) ans += a[i];
	deque<ll> a1, a2, a3;
	for (int i = 0; i < l; ++i) a1.push_back(a[i]);
	for (int i = l; i <= r; ++i) a2.push_back(a[i]);
	for (int i = r + 1; i < n; ++i) a3.push_back(a[i]);
	sort(a1.begin(), a1.end()); sort(a2.begin(), a2.end()); sort(a3.begin(), a3.end());

	ll tans = 0;
	while (!a1.empty() && !a2.empty() && a1.front() < a2.back()) {
		tans += a1.front(); a1.pop_front();
		tans -= a2.back(); a2.pop_back();
	}
	a2.clear();
	for (int i = l; i <= r; ++i) a2.push_back(a[i]); sort(a2.begin(), a2.end());

	ll ttans = 0;
	while (!a3.empty() && !a2.empty() && a3.front() < a2.back()) {
		// cout << a3.front() << ' '<< a2.back() << '\n';
		ttans += a3.front(); a3.pop_front();
		ttans -= a2.back(); a2.pop_back();
	}
	cout << ans + min(tans, ttans) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}