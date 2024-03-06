#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n; cin >> n;
	char s[n + 1]; for (int i = 1; i <= n; ++i) cin >> s[i];
	ll lsum[n + 1], rsum[n + 1], lisum[n + 1], risum[n + 1];
	lsum[0] = 0, rsum[0] = 0, lisum[0] = 0, risum[0] = 0;
	for (int i = 1; i <= n; ++i) {
		lsum[i] = lsum[i - 1] + (s[i] == '<');
		rsum[i] = rsum[i - 1] + (s[i] == '>');
		lisum[i] = lisum[i - 1] + i * (s[i] == '<');
		risum[i] = risum[i - 1] + i * (s[i] == '>');
	}
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '>') {
			if (rsum[i] > lsum[n] - lsum[i]) {
				ll p = lower_bound(rsum + 1, rsum + n + 1, rsum[i] - lsum[n] + lsum[i]) - rsum;
				ll ans = 2 * ((lisum[n] - lisum[i]) - (risum[i] - risum[p - 1]));
				ans += n + 1 + i;
				cout << ans << ' ';
			} else {
				ll p = lower_bound(lsum + 1, lsum + n + 1, rsum[i] + lsum[i]) - lsum;
				ll ans = 2 * ((lisum[p] - lisum[i]) - (risum[i]));
				ans += i;
				cout << ans << ' ';
			}
		} else {
			if (rsum[i] >= lsum[n] - lsum[i - 1]) {
				ll p = lower_bound(rsum + 1, rsum + n + 1, rsum[i] - lsum[n] + lsum[i - 1] + 1) - rsum;
				ll ans = 2 * ((lisum[n] - lisum[i - 1]) - (risum[i] - risum[p - 1]));
				ans += n + 1 - i;
				cout << ans << ' ';
			} else {
				ll p = lower_bound(lsum + 1, lsum + n + 1, rsum[i] + lsum[i]) - lsum;
				ll ans = 2 * ((lisum[p] - lisum[i - 1]) - (risum[i]));
				ans -= i;
				cout << ans << ' ';
			}
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}