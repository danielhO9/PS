#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> ans;
	int cnt = 0;
	while (true) {
		int mina = 1e9; int maxa = 0;
		for (int i = 0; i < n; ++i) {
			mina = min(mina, a[i]);
			maxa = max(maxa, a[i]);
		}
		if (mina == maxa) break;
		if (mina % 2 == 0) {
			for (int i = 0; i < n; ++i) a[i] /= 2;
			ans.push_back(0);
		} else {
			for (int i = 0; i < n; ++i) {
				++a[i];
				a[i] /= 2;
			}
			ans.push_back(1);
		}
		++cnt;
	}
	cout << cnt << '\n';
	if (cnt <= n) {
		for (auto i: ans) cout << i << ' ';
		cout << '\n';
	}
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}