#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll a[200000];

bool pos(int k) {
	ll now = 0;
	int idx = 0;
	for (ll i = k; i >= 1; --i) {
		now += i;
		while (idx < N && a[idx] < now) ++idx;
		if (idx >= N - 1) return true;
		++idx;
	}
	return false;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	sort(a, a + N);
	ll l = 0, r = N;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (pos(mid)) r = mid;
		else l = mid;
	}
	cout << min(a[N - 1], r * (r + 1) / 2) << '\n';
	// cout << pos(3);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}