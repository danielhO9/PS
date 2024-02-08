#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 1000000007;

vector<pair<LL, int>> table;

void solve() {
	LL l, r; cin >> l >> r; --l;
	LL rans = 0, lans = 0;
	for (int i = 0; i < table.size(); ++i) {
		if (table[i + 1].first <= r) rans += table[i].second * ((table[i + 1].first - table[i].first) % MOD);
		else {
			rans += table[i].second * ((r - table[i].first + 1) % MOD); rans %= MOD;
			break;
		}
		rans %= MOD;
	}
	for (int i = 0; i < table.size(); ++i) {
		if (table[i + 1].first <= l) lans += table[i].second * ((table[i + 1].first - table[i].first) % MOD);
		else {
			lans += table[i].second * ((l - table[i].first + 1) % MOD); lans %= MOD;
			break;
		}
		lans %= MOD;
	}
	cout << (rans + MOD - lans) % MOD << '\n';
}

void init() {
	table.push_back({3, 0});
	for (LL i = 2; i <= 60; ++i) {
		int times = i / log2(i);
		table.push_back({1LL << i, times});
		if (i == 60) break;
		LL x = 1;
		for (int j = 0; j < times; ++j) x *= i;
		while (true) {
			if (ceil((double)(1LL << (i + 1)) / x) <= i) break;
			x *= i;
			table.push_back({x, ++times});
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
	// for (auto [i, j]: table) {
	// 	cout << i << ' ' << j << '\n';
	// }
}