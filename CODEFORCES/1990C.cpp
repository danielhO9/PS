#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	ll a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	ll sum = 0;
	vector<int> cnt(n + 1);
	vector<ll> arr;
	ll MAD = 0ll;
	for (int i = 0; i < n; ++i) {
		++cnt[a[i]];
		if (cnt[a[i]] >= 2) MAD = max(MAD, a[i]);
		arr.push_back(MAD);
		sum += a[i];
	}
	// for (auto i: arr) cout << i << ' ';
	// cout << '\n';
	for (auto i: arr) sum += i;
	for (int i = 1; i < n - 1; ++i) {
		if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) arr[i] = arr[i - 1];
	}
	if (n == 1) arr[n - 1] = 0;
	else {
		if (arr[n - 1] != arr[n - 2]) arr[n - 1] = arr[n - 2];
	}
	// for (auto i: arr) cout << i << ' ';
	// cout << '\n';
	for (ll i = 0; i < n; ++i) {
		sum += arr[i] * (n - i - 1);
	}
	cout << sum << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}