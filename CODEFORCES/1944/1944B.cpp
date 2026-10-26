#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(2 * n + 1); for (int i = 1; i <= 2 * n; ++i) cin >> a[i];
	vector<int> cnt[n + 1];
	for (int i = 1; i <= 2 * n; ++i) {
		cnt[a[i]].push_back(i);
	}
	vector<int> a1, a2, a3;
	for (int i = 1; i <= n; ++i) {
		if (cnt[i].front() <= n && cnt[i].back() <= n) {
			a1.push_back(i);
		} else if (cnt[i].front() > n && cnt[i].back() > n){
			a2.push_back(i);
		} else a3.push_back(i);
	}
	int sz = a1.size();
	sz = min(sz, k);
	for (int i = 0; i < sz; ++i) {
		cout << a1[i] << ' ' << a1[i] << ' ';
	}
	for (int i = 0; i < 2 * (k - sz); ++i) {
		cout << a3[i] << ' ';
	}
	cout << '\n';
	for (int i = 0; i < sz; ++i) {
		cout << a2[i] << ' ' << a2[i] << ' ';
	}
	for (int i = 0; i < 2 * (k - sz); ++i) {
		cout << a3[i] << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}