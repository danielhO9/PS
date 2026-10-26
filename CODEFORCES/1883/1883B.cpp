#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<int> cnt(26);
	for (auto i: s) ++cnt[i - 'a'];
	int odd = 0;
	for (auto i: cnt) {
		if (i % 2 == 1) ++odd; 
	}
	if ((n - k) % 2 == 0) {
		if (odd > k) {
			cout << "NO" << '\n';
			return;
		} else {
			cout << "YES" << '\n';
			return;
		}
	} else {
		if (odd - 1 > k || (k - (odd - 1)) % 2 == 1) {
			cout << "NO" << '\n';
			return;
		} else {
			cout << "YES" << '\n';
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}