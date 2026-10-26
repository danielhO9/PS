#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int l, r; cin >> l >> r;
	int cnt = r - l + 1;
	cnt /= 2;
	if (l % 2 && r % 2) ++cnt;
	cout << cnt / 2 << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}