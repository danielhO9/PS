#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> zero;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '0') zero.push_back(i);
	}
	LL ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (zero.empty()) cout << -1 << ' ';
		else {
			ans += (LL) i - zero.back();
			zero.pop_back();
			cout << ans << ' ';
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}