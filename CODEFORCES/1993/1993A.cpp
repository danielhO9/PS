#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int cnt[4]; memset(cnt, 0, sizeof(cnt));
	int tcnt = 0;
	for (int i = 0; i < 4 * n; ++i) {
		if (s[i] != '?') ++cnt[s[i] - 'A'];
		else ++tcnt;
	}
	// for (int i = 0; i < 4; ++i) cout << cnt[i] << ' ';
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		ans += min(cnt[i], n);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}