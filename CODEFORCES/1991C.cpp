#include <bits/stdc++.h>
using namespace std;

int n;
int a[200000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n - 1; ++i) {
		if ((a[i] + a[i + 1]) % 2) {
			cout << -1 << '\n';
			return;
		}
	}
	int cnt = 0;
	vector<int> ans;
	while (true) {
		if (cnt == 41) break;
		bool flag = true;
		for (int i = 0; i < n; ++i) if (a[i] != 0) {
			flag = false;
		}
		if (flag) {
			cout << cnt << '\n';
			for (auto i: ans) cout << i << ' ';
			cout << '\n';
			return;
		}
		sort(a, a + n);
		int x = (a[n - 1] + a[0]) / 2;
		++cnt; ans.push_back(x);
		for (int i = 0; i < n; ++i) a[i] = abs(a[i] - x);
	}
	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}