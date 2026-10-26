#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;

ll val(string& ss) {
	vector<ll> cnt(26);
	for (auto i: ss) ++cnt[i - 'a'];
	ll ret = 1;
	for (ll i = 1; i <= ss.size(); ++i) ret *= i;
	for (int i = 0; i < 26; ++i) {
		for (ll j = 1; j <= cnt[i]; ++j) ret /= j;
	}
	return ret;
}

void solve() {
	cin >> n;
	cin >> s;
	string ans = s;
	ll v = LLONG_MAX;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
		string ss = s;
		ss[i] = s[j];
		ll tmp = val(ss);
		if (v > tmp) {
			ans = ss;
			v = tmp;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}