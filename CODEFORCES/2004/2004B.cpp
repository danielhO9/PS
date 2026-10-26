#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int l, r, L, R;

void solve() {
	cin >> l >> r >> L >> R;
	if (r < L || R < l) {
		cout << 1 << '\n';
		return;
	}
	int s = max(l, L);
	int e = min(r, R);
	int ans = e - s + 2;
	if (s == l && s == L) --ans;
	if (e == r && e == R) --ans;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}