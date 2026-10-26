#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	int cnt[51]; memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; ++i) {
		int tmp; cin >> tmp;
		++cnt[tmp];
	}
	for (int i = n; i >= 1; --i) {
		if (cnt[i] % 2 == 1) {
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