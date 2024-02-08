#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	int a = 'a';
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			cout << char(a + j);
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}