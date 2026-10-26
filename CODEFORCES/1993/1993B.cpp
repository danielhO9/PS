#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[200000];

void solve() {
	cin >> n;
	int ocnt = 0, ecnt = 0;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) if (a[i] % 2 == 0) ++ecnt;
	ocnt = n - ecnt;
	if (ecnt == n) {
		cout << 0 << '\n';
		return;
	}
	if (ocnt == n) {
		cout << 0 << '\n';
		return;
	}
	vector<ll> v;
	for (int i = 0; i < n; ++i) if (a[i] % 2 == 0) v.push_back(a[i]);
	sort(v.begin(), v.end());
	ll maxo = 0, maxe = 0;
	for (int i = 0; i < n; ++i) if (a[i] % 2 == 1) maxo = max(maxo, a[i]);
	for (int i = 0; i < n; ++i) if (a[i] % 2 == 0) maxe = max(maxe, a[i]);
	int ans = 0;
	for (auto i: v) {
		if (maxo > i) {
			++ans;
			maxo += i;
		} else {
			ans += 2;
			maxo += maxe;
			maxo += i;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}