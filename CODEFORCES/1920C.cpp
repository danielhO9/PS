#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

bool available(vector<int>& a, int k, int& n) {
	if (k == n) return true;
	int m = abs(a[0] - a[k]);
	for (int i = 0; i < k; ++i) {
		int j = i + k;
		while (j < n) {
			if (a[i] != a[j]) m = gcd(m, abs(a[i] - a[j]));
			j += k;
		}
	}
	if (m == 1) return false;
	return true;
}

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	int ans = 0;
	for (int i = 1; i <= n; ++i) if (n % i == 0) {
		if (available(a, i, n)) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}