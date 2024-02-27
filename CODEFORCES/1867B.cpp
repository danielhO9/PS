#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int h = n / 2;
	int cnt = 0;
	for (int i = 0; i < h; ++i) {
		if (s[i] != s[n - 1 - i]) ++cnt;
	}
	for (int i = 0; i <= n; ++i) {
		if (n % 2 == 0) {
			if (cnt <= i && i <= cnt + (h - cnt) * 2 && (i - cnt) % 2 == 0) cout << 1;
			else cout << 0;
		} else {
			if (cnt <= i && i <= cnt + (h - cnt) * 2 + 1) cout << 1;
			else cout << 0;
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}