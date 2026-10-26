#include <bits/stdc++.h>
using namespace std;

bool check(int& n, int& k, vector<pair<int, int>>& P) {
	if (__builtin_popcount(k) > n / 5) return false;
	for (int i = 1; i <= n; ++i) {
		if (k >> i & 1) {
			for (int j = 2 * i; j <= n; j += i) k ^= (1 << j);
		}
	}
	for (auto i: P) {
		if ((k >> i.first) & ~(k >> i.second) & 1) return false;
	}
	// for (int i = n; i >= 1; --i) cout << (k >> i & 1);
	// cout << '\n';
	return true;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<pair<int, int>> P;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		P.push_back({u, v});
	}
	if (n >= 20) {
		cout << n << '\n';
		for (int i = 1; i <= n; ++i) cout << i << ' ';
		cout << '\n';
		return;
	}
	int ans = -1;
	for (int x = 1; x <= n; ++x) {
		if (ans > 0) break;
		int temp = 1 << x;
		if (check(n, temp, P)) ans = temp;
		for (int y = 1; y < x; ++y) {
			if (ans > 0) break;
			temp = (1 << x) | (1 << y);
			if (check(n, temp, P)) ans = temp;
			for (int z = 1; z < y; ++z) {
				if (ans > 0) break;
				temp = (1 << x) | (1 << y) | (1 << z);
				if (check(n, temp, P)) ans = temp;
			}
		}
	}
	if (ans == -1) {
		cout << -1 << '\n';
		return;
	}
	cout << __builtin_popcount(ans) << '\n';
	for (int i = 1; i <= n; ++i) if (ans >> i & 1) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}