#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll l[200000], r[200000];
ll cnt[400001];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
	string ans = "";
	for (int i = 0; i <= 2 * n; ++i) {
		cnt[i] = 0;
	}
	vector<int> sum(2 * n + 1, 0);
	for (int i = 0; i < n; ++i) {
		if (l[i] == r[i]) ++cnt[l[i]];
	}
	for (int i = 1; i <= 2 * n; ++i) {
		sum[i] = sum[i - 1] + (cnt[i] > 0);
	}
	for (int i = 0; i < n; ++i) {
		if (l[i] == r[i]) {
			if (cnt[l[i]] > 1) {
				ans += '0';
			} else {
				ans += '1';
			}
		} else {
			ll tmp = sum[r[i]] - sum[l[i] - 1];
			if (tmp == r[i] - l[i] + 1) {
				ans += '0';
			} else ans += '1';
		}
	}
	cout << ans << '\n';



}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}