#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		if (i * (n - i) <= k) {
			cout << i << '\n';
			return ;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}