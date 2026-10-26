#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[200];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 1; i < n; ++i) {
		int mn = min(a[i], a[i - 1]);
		int mx = max(a[i], a[i - 1]);
		if (mx < 2 * mn) {
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}