#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;

void solve() {
	cin >> n >> k;
	vector<int> ans(n, -1);
	int num = 0;
	for (int i = k - 1; i < n; i += k) {
		ans[i] = ++num;
	}
	for (int i = 0; i < n; ++i) {
		if (ans[i] == -1) ans[i] = ++num;
	}
	for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}