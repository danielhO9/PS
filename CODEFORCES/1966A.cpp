#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> c(n); for (int i= 0; i < n; ++i) cin >> c[i];
	vector<int> cnt(101);
	for (int i = 0; i < n; ++i) ++cnt[c[i]];
	for (int i = 1; i <= 100; ++i) if (cnt[i] >= k) {
		cout << k - 1 << '\n';
		return;
	}
	cout << n << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}