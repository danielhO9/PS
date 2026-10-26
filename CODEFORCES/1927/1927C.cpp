#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> b(m); for (int i = 0; i < m; ++i) cin >> b[i];
	vector<int> cnt(k + 1);
	for (int i = 0; i < n; ++i) {
		if (a[i] <= k) cnt[a[i]] = 1;
	}
	for (int i = 0; i < m; ++i) {
		if (b[i] <= k) {
			if (cnt[b[i]] == 0) cnt[b[i]] = 2;
			else if (cnt[b[i]] == 1) cnt[b[i]] = 3;
		}
	}
	int acnt = 0, bcnt = 0, both = 0;
	for (int i = 1; i <= k; ++i) {
		if (cnt[i] == 0) {
			cout << "NO\n"; return;
		} else if (cnt[i] == 1) ++acnt;
		else if (cnt[i] == 2) ++bcnt;
		else ++both;
	}
	if (acnt <= k / 2 && bcnt <= k / 2) {
		cout << "YES\n"; return;
	}
	cout << "NO\n"; return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}