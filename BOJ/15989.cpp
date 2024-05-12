#include <bits/stdc++.h>
using namespace std;

int ans[10001];

void init() {
	ans[1] = 1;
	ans[2] = 2;
	ans[3] = 3;
	for (int i = 4; i <= 10000; ++i) ans[i] = ans[i - 3] + i / 2 + 1;
}

void solve() {
	int n; cin >> n;
	cout << ans[n] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}