#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;

void solve() {
	cin >> n >> s;
	int mn = 0, mx = 1, cur = 1;
	int dif = 1;
	for (int i = 1; i < n; ++i) {
		if (s[i] == s[i - 1]) {
			dif *= -1;
			cur += dif;
		} else {
			cur += dif;
		}
		mx = max(mx, cur);
		mn = min(mn, cur);
	}
	cout << mx - mn << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}