#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<int> x(n); for (int i = 0; i < n; ++i) cin >> x[i];
	if (n != 2) {
		cout << "NO\n";
		return;
	}
	if (x[0] + 1 < x[1]) {
		cout << "YES\n";
	} else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}