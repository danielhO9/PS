#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	int k = (n + 1) / 2;
	sort(a.begin(), a.end());
	int ans = 0;
	for (int i = k - 1; i < n; ++i) {
		if (a[i] == a[k - 1]) ++ans;
		else break;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}