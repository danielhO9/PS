#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; ++i) sum += i * (2 * i - 1);
	cout << sum << ' ' << n * 2 << '\n';
	for (int i = n; i >= 1; --i) {
		cout << 1 << ' ' << i << ' ';
		for (int j = 1; j <= n; ++j) cout << j << ' ';
		cout << '\n';
		cout << 2 << ' ' << i << ' ';
		for (int j = 1; j <= n; ++j) cout << j << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}