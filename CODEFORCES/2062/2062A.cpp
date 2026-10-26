#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	int ans = 0;
	for (auto i: s) if (i == '1') ++ans;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}